/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "Grammer.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
class Parser
  : public Grammer
{
 public:
  Parser() = default;
  ~Parser() override = default;

 protected:
  std::any appendRule(const List& args) override;
  std::any onSemantics(const List& args) override;
  std::any appendSemantics(const List& args) override;
  std::any onSemantic(const List& args) override;
  std::any onTokens(const List& args) override;
  std::any appendTokens(const List& args) override;
  std::any tokenRule(const List& args) override;
  std::any tokenString(const List& args) override;
  std::any tokenRegexp(const List& args) override;
  std::any onActionRule(const List& args) override;
  std::any onActionArg(const List& args) override;
  std::any onArgs(const List& args) override;
  std::any appendArgs(const List& args) override;
  std::any onArg(const List& args) override;
};
/***********************************************************************//**
	$Id$
***************************************************************************/
