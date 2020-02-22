/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "Semantic.hpp"
/***********************************************************************//**
	@brief ルール
***************************************************************************/
class Rule {
 private:
  std::string name_;
  std::shared_ptr<Semantics> semantics_;

 public:
  Rule(const std::string& name, 
       const std::shared_ptr<Semantics>& semantics);
  ~Rule() = default;

  std::string toString() const;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Rules
  : public std::vector<std::shared_ptr<Rule>>
{
};
