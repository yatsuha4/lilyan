/***********************************************************************//**
	@file
***************************************************************************/
#include "Action.hpp"
#include "Parser.hpp"
#include "Token.hpp"
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
void Action::Arg::prematch(Output& output) const {
  output << "std::any _arg;" << '\n';
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
/***********************************************************************//**
	@brief 
***************************************************************************/
Action::Const::Const(const std::string& value)
  : value_(value)
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Action::Const::prematch(Output& output) const {
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Const::match(size_t index, 
                                 const Rule& rule, 
                                 const Token& token) const {
  return token.toCpp(rule, "");
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Const::postmatch(Parser& parser) const {
  return value_;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
Action::Func::Func(const std::string& name, const std::vector<int>& args)
  : name_(name), 
    args_(args)
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Action::Func::prematch(Output& output) const {
  if(!args_.empty()) {
    output << "std::array<std::any, " << args_.size() << "> _args;" << '\n';
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Func::match(size_t index, 
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
std::string Action::Func::postmatch(Parser& parser) const {
  std::ostringstream stream;
  stream << "std::make_shared<lilyan::Action>(\"" << name_
         << "\", [this";
  if(!args_.empty()) {
    stream << ", _args";
  }
  stream << "]() { return " << name_ << "(";
  for(size_t i = 0; i < args_.size(); i++) {
    if(i > 0) {
      stream << ", ";
    }
    stream << "eval(_args.at(" << i << "))";
  }
  stream << "); })";
  return stream.str();
}

