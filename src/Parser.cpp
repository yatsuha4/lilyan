﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "Parser.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArgs(const List& args) {
  List v;
  v.push_back(args[1]);
  return std::any(v);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::appendArgs(const List& args) {
  auto v = std::any_cast<List>(args[1]);
  v.push_back(args[2]);
  return std::any(v);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArg(const List& args) {
  return std::any(std::stoi(std::any_cast<std::string>(args[1])));
}
/***********************************************************************//**
	$Id$
***************************************************************************/
