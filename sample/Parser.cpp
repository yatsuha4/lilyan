/***********************************************************************//**
	@file
***************************************************************************/
#include "Parser.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::parse(const std::string& text) {
  getInput().set("", std::make_shared<std::string>(text));
  std::any result;
  if(rule_main(&result)) {
    return eval(result);
  }
  return std::any();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onAdd(const std::any& lhs, const std::any& rhs) {
  return std::any_cast<int>(lhs) + std::any_cast<int>(rhs);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onSub(const std::any& lhs, const std::any& rhs) {
  return std::any_cast<int>(lhs) - std::any_cast<int>(rhs);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onMul(const std::any& lhs, const std::any& rhs) {
  return std::any_cast<int>(lhs) * std::any_cast<int>(rhs);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onDiv(const std::any& lhs, const std::any& rhs) {
  return std::any_cast<int>(lhs) / std::any_cast<int>(rhs);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onNumber(const std::smatch& value) {
  return std::stoi(value[0].str());
}
