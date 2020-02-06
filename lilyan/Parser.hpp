/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

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
    return !input.isEnd();
  }

  virtual void error(const Input& input) {
    throw Error(input.toString());
  }
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
