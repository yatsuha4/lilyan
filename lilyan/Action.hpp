/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace lilyan {
class Parser;
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action {
 public:
  using Func = std::any(Parser::*)(const List&);

 public:
  const char* name;
  Func func;

 public:
  Action(const char* name, Func func)
    : name(name), 
      func(func)
  {}
  Action(const Action& src) = default;
};
}
