/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "lilyan/Input.hpp"

namespace lilyan {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Parser {
 public:
  using List = std::vector<std::any>;
  using action_t = std::any(Parser::*)(const List&);

  class Action {
   public:
    const char* name;
    action_t action;

   public:
    Action(const char* name, action_t action)
      : name(name), 
        action(action)
    {}
    Action(const Action& src) = default;
  };

  class Error {
   private:
    std::string message_;

   public:
    Error(const std::string& message) : message_(message) {}
    ~Error() = default;

    const std::string& getMessage() const {
      return message_;
    }
  };

 public:
  std::any eval(const std::any& value) {
    if(value.type() == typeid(std::shared_ptr<List>)) {
      auto list = std::any_cast<std::shared_ptr<List>>(value);
      for(auto& item : *list) {
        item = eval(item);
      }
      if(list->size() > 0 && list->at(0).type() == typeid(Action)) {
        return (this->*(std::any_cast<Action>(list->at(0)).action))(*list);
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

 protected:
  Parser() = default;
  virtual ~Parser() = default;

  bool append(List& list, const std::any& value) {
    if(value.has_value()) {
      list.push_back(value);
      return true;
    }
    return false;
  }

  virtual std::any getToken(Input& input, const std::string& pattern) {
    return skip(input) ? input.match(pattern) : std::any();
  }

  virtual std::any getToken(Input& input, const std::regex& pattern) {
    return skip(input) ? input.match(pattern) : std::any();
  }

  virtual bool skip(Input& input) {
    //return !input.isEnd();
    return true;
  }

  virtual void error(const Input& input) {
    throw Error(input.toString());
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
