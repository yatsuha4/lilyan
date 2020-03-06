/***********************************************************************//**
	@file
***************************************************************************/
#include "Action.hpp"
#include "Parser.hpp"
#include "Token.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::GetArg(size_t index) {
  std::ostringstream stream;
  stream << "args.at(" << index << ")";
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
void Action::Arg::prematch(Output& output) const {
  output << "std::any arg;" << '\n';
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Arg::match(size_t index, 
                               const Rule& rule, 
                               const Token& token) {
  return token.toCpp(rule, (index + 1 == index_) ? "arg" : "");
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Arg::postmatch(Parser& parser) const {
  return "arg";
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
                                 const Token& token) {
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
    args_(args), 
    types_(args.size(), typeid(Token))
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Action::Func::prematch(Output& output) const {
  if(!args_.empty()) {
    output << "std::array<std::any, " << args_.size() << "> args;" << '\n';
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Action::Func::match(size_t index, 
                                const Rule& rule, 
                                const Token& token) {
  auto iter = std::find(args_.begin(), args_.end(), index + 1);
  if(iter != args_.end()) {
    auto index = iter - args_.begin();
    types_[index] = typeid(token);
    return token.toCpp(rule, GetArg(index));
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
    stream << ", args";
  }
  stream << "]() { return " << name_ << "(";
  for(size_t i = 0; i < args_.size(); i++) {
    if(i > 0) {
      stream << ", ";
    }
    if(types_[i] == typeid(Token::Regexp)) {
      stream << "std::any_cast<std::smatch>(" << GetArg(i) << ")";
    }
    else if(types_[i] == typeid(Token::String)) {
      stream << "std::any_cast<std::string>(" << GetArg(i) << ")";
    }
    else {
      stream << GetArg(i);
    }
  }
  stream << "); })";
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Action::Func::declare(Output& output) const {
  output << "virtual std::any " << name_ << "(";
  for(auto iter = types_.begin(); iter != types_.end(); iter++) {
    if(iter != types_.begin()) {
      output << ", ";
    }
    if(*iter == typeid(Token::Regexp)) {
      output << "const std::smatch&";
    }
    else if(*iter == typeid(Token::String)) {
      output << "const std::string&";
    }
    else {
      output << "const std::any&";
    }
  }
  output << ") = 0;" << '\n';
}
