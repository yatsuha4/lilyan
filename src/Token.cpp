﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "Token.hpp"
#include "Rule.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Token::toString() const {
  return getValue();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Token::Regexp::toString() const {
  std::ostringstream stream;
  stream << "/" << getValue() << "/";
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Token::Regexp::toCpp(const ::Rule& rule) const {
  std::ostringstream stream;
  stream << "getToken(std::regex(R\"(" << getValue() << ")\"))";
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Token::Rule::toString() const {
  return getValue();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Token::Rule::toCpp(const ::Rule& rule) const {
  std::ostringstream stream;
  if(rule.getName() == getValue()) {
    stream << "value";
  }
  else {
    stream << getValue() << "()";
  }
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Token::String::toString() const {
  std::ostringstream stream;
  stream << "\"" << getValue() << "\"";
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Token::String::toCpp(const ::Rule& rule) const {
  std::ostringstream stream;
  stream << "getToken(std::string(\"";
  for(auto c : getValue()) {
    switch(c) {
    case '\"':
      stream << "\\\"";
      break;
    default:
      stream << c;
      break;
    }
  }
  stream << "\"))";
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Tokens::isRecursive(const std::string& name) const {
  for(auto& token : *this) {
    if(auto rule = std::dynamic_pointer_cast<Token::Rule>(token)) {
      if(rule->getValue() == name) {
        return true;
      }
    }
  }
  return false;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Tokens::toString() const {
  std::ostringstream stream;
  for(auto iter = begin(); iter != end(); iter++) {
    if(iter != begin()) {
      stream << " ";
    }
    stream << (*iter)->toString();
  }
  return stream.str();
}