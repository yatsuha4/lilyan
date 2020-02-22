/***********************************************************************//**
	@file
***************************************************************************/
#include "Action.hpp"
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
Action::Action(const std::string& name, const std::vector<int>& args)
  : name_(name), 
    args_(args)
{
}
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
Action::Action(const std::vector<int>& args)
  : args_(args)
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::toString() const {
  if(name_.empty()) {
    return argsToString();
  }
  std::ostringstream stream;
  stream << name_ << "(" << argsToString() << ")";
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::argsToString() const {
  std::ostringstream stream;
  for(auto iter = args_.begin(); iter != args_.end(); iter++) {
    if(iter != args_.begin()) {
      stream << ", ";
    }
    stream << "$" << *iter;
  }
  return stream.str();
}
