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
  using Func = std::function<std::any()>;

 public:
  const char* name;
  Func func;

 public:
  Action(const char* name, Func func)
    : name(name), 
      func(func)
  {}
};
}
