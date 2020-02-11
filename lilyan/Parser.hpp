/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "lilyan/Input.hpp"
#include "lilyan/Semantic.hpp"

namespace lilyan {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Parser {
 public:
  using List = std::vector<std::any>;
  using func_t = std::any(Parser::*)(const List&);

  class Func {
   public:
    const char* name;
    func_t func;

   public:
    Func(const char* name, func_t func)
      : name(name), 
        func(func)
    {}
    Func(const Func& src) = default;
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

  std::any eval(const std::any& value) {
    if(value.type() == typeid(std::shared_ptr<List>)) {
      auto list = std::any_cast<std::shared_ptr<List>>(value);
      for(auto& item : *list) {
        item = eval(item);
      }
      if(list->size() > 0 && list->at(0).type() == typeid(Func)) {
        return (this->*(std::any_cast<Func>(list->at(0)).func))(*list);
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
    else if(value.type() == typeid(Func)) {
      return std::string(std::any_cast<Func>(value).name);
    }
    return std::string("?");
  }

 protected:
  Parser() = default;
  virtual ~Parser() = default;

  bool append(Semantic& semantic, Input& input, const std::any& value) {
    return skip(input) && semantic.append(value);
  }

  bool append(List& list, const std::any& value) {
    if(value.has_value()) {
      list.push_back(value);
      return true;
    }
    return false;
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
