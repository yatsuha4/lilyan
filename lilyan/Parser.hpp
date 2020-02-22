/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "lilyan/Action.hpp"
#include "lilyan/Error.hpp"
#include "lilyan/Input.hpp"

namespace lilyan {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Parser {
 private:
  Input input_;

 public:
  std::any eval(const std::any& value) {
    if(value.type() == typeid(std::shared_ptr<List>)) {
      auto list = std::any_cast<std::shared_ptr<List>>(value);
      for(auto& item : *list) {
        item = eval(item);
      }
      if(list->size() > 0 && list->at(0).type() == typeid(Action)) {
        return (this->*(std::any_cast<Action>(list->at(0)).func))(*list);
      }
    }
    return value;
  }

  void dump(std::ostream& output, 
            const std::any& value, 
            const std::string& indent = "") const {
    if(value.type() == typeid(std::shared_ptr<List>)) {
      auto& list = *std::any_cast<std::shared_ptr<List>>(value);
      for(auto iter = list.begin(); iter != list.end(); iter++) {
        if(iter == list.begin()) {
          if(!indent.empty()) {
            output << std::endl << indent;
          }
          output << "(";
        }
        else {
          output << " ";
        }
        dump(output, *iter, indent + "  ");
      }
      output << ")";
    }
    else {
      output << toString(value);
    }
    if(indent.empty()) {
      output << std::endl;
    }
  }

  virtual std::string toString(const std::any& value) const {
    if(value.type() == typeid(std::string)) {
      std::ostringstream stream;
      stream << "'" << std::any_cast<std::string>(value) << "'";
      return stream.str();
    }
    else if(value.type() == typeid(Action)) {
      return std::string(std::any_cast<Action>(value).name);
    }
    return std::string("?");
  }

  virtual void error(const std::string& message) {
    std::ostringstream stream;
    stream << message << " at " << getInput().toString();
    throw Error(stream.str());
  }

 protected:
  Parser() = default;
  virtual ~Parser() = default;

  Input& getInput() {
    return input_;
  }

  bool append(List& list, const std::any& value) {
    if(value.has_value()) {
      list.push_back(value);
      return true;
    }
    return false;
  }

  virtual std::any getToken(const std::string& pattern) {
    return skip() ? onGetToken(pattern) : std::any();
  }

  virtual std::any onGetToken(const std::string& pattern) {
    return getInput().match(pattern);
  }

  virtual std::any getToken(const std::regex& pattern) {
    return skip() ? onGetToken(pattern) : std::any();
  }

  virtual std::any onGetToken(const std::regex& pattern) {
    return getInput().match(pattern);
  }

  virtual bool skip() {
    for(size_t i = 0;; i++) {
      auto c = input_.fetch(i);
      if(c == '\0') {
        return false;
      }
      else if(c < '\0' || c > ' ') {
        input_.seek(i);
        break;
      }
    }
    return true;
  }

  std::any checkValue(const std::any& value) {
    assert(value.has_value());
    return value;
  }
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
