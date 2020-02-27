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
Action::Action(int arg) {
  args_.push_back(arg);
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
  if(!args_.empty()) {
    stream << "std::array<std::any, " << args_.size() << "> _args;";
  }
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::match(size_t index, 
                          const Rule& rule, 
                          const Token& token) const {
  auto iter = std::find(args_.begin(), args_.end(), index + 1);
  if(iter != args_.end()) {
    std::ostringstream arg;
    arg << "_args.at(" << (iter - args_.begin()) << ")";
    return token.toCpp(rule, arg.str());
  }
  return token.toCpp(rule, "");
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::postmatch(Parser& parser) const {
  std::ostringstream stream;
  if(hasFunc()) {
    stream << "std::make_shared<lilyan::Action>(\"" << getName()
           << "\", [this";
    if(!args_.empty()) {
      stream << ", _args";
    }
    stream << "]() { return " << getName() << "(";
    for(size_t i = 0; i < args_.size(); i++) {
      if(i > 0) {
        stream << ", ";
      }
      stream << "eval(_args.at(" << i << "))";
    }
    stream << "); })";
  }
  else {
    stream << "_args.at(0)";
  }
  return stream.str();
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
/***********************************************************************//**
	@brief 
***************************************************************************/
Action::Arg::Arg(int index)
  : index_(index)
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Arg::prematch() const {
  return std::string("std::any _arg");
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Arg::match(size_t index, 
                               const Rule& rule, 
                               const Token& token) const {
  return token.toCpp(rule, (index + 1 == index_) ? "_arg" : "");
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Arg::postmatch(Parser& parser) const {
  return "_arg";
}
