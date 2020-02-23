/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "Action.hpp"
#include "Output.hpp"
#include "Token.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
class Semantic {
 private:
  std::shared_ptr<Tokens> tokens_;
  std::shared_ptr<Action> action_;

 public:
  Semantic(const std::shared_ptr<Tokens>& tokens, 
           const std::shared_ptr<Action>& action);
  ~Semantic() = default;

  bool isRecursive(const std::string& name) const;
  void putCpp(Parser& output, const Rule& rule) const;

  std::string toString() const;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Semantics
  : public std::vector<std::shared_ptr<Semantic>>
{
  using super = std::vector<std::shared_ptr<Semantic>>;

 public:
  Semantics() = default;
  ~Semantics() = default;
};
