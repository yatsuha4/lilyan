/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "Output.hpp"
#include "Semantic.hpp"
/***********************************************************************//**
	@brief ルール
***************************************************************************/
class Rule {
 private:
  std::string name_;
  Semantics semantics_;
  Semantics recursiveSemantics_;

 public:
  Rule(const std::string& name, const Semantics& semantics);
  ~Rule() = default;

  const auto& getName() const {
    return name_;
  }

  std::string toString() const;

  void putCpp(Parser& parser) const;
  std::string getCppReturn(const std::string& value) const;

 private:
  bool hasRecursive() const;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Rules
  : public std::vector<std::shared_ptr<Rule>>
{
};
