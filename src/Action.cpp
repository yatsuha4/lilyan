/***********************************************************************//**
	@file
***************************************************************************/
#include "Action.hpp"
#include "Parser.hpp"
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
std::string Action::prematch() const {
  std::ostringstream stream;
  if(hasFunc()) {
    stream << "auto result = std::make_shared<lilyan::List>("
           << (args_.size() + 1) << ");";
  }
  else {
    stream << "std::any result;";
  }
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::match(size_t index, const std::string& value) const {
  auto iter = std::find(args_.begin(), args_.end(), index + 1);
  if(iter != args_.end()) {
    std::ostringstream stream;
    if(hasFunc()) {
      stream << "(result->at(" << ((iter - args_.begin()) + 1) << ") = "
             << value << ")";
    }
    else {
      stream << "(result = " << value << ")";
    }
    return stream.str();
  }
  return value;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::postmatch(Parser& parser) const {
  if(hasFunc()) {
    std::ostringstream stream;
    stream << "result->at(0) = lilyan::Action(\"" << getName()
           << "\", static_cast<lilyan::Action::Func>(&"
           << parser.getClassName() << "::" << getName()
           << "))";
    return stream.str();
  }
  return std::string();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Action::hasFunc() const {
  return !name_.empty();
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
