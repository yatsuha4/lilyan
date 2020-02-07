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

 protected:
  Parser() = default;
  virtual ~Parser() = default;

  bool append(Semantic& semantic, Input& input, const std::any& value) {
    return skip(input) && semantic.append(value);
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
