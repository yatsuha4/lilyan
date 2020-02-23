/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "Grammer.hpp"
#include "Token.hpp"
#include "Semantic.hpp"
#include "Output.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
class Parser
  : public Grammer
{
  using super = Grammer;

 private:
  std::string className_;
  Output output_;
  std::vector<std::shared_ptr<Action>> actions_;

 public:
  Parser();
  ~Parser() override = default;

  Parser& setClassName(const decltype(className_)& className) {
    className_ = className;
    return *this;
  }

  const auto& getClassName() const {
    return className_;
  }

  auto& getOutput() {
    return output_;
  }

  void parse(const std::string& file);
  void puts(const std::string& text);

 protected:
  std::any onGetToken(const std::string& pattern) override;

  std::any onRules(std::any) override;
  std::any appendRules(std::any, std::any) override;
  std::any onRule(std::any, std::any) override;
  std::any onSemantics(std::any) override;
  std::any appendSemantics(std::any, std::any) override;
  std::any onSemantic(std::any, std::any) override;
  std::any onTokens(std::any) override;
  std::any appendTokens(std::any, std::any) override;
  std::any tokenRule(std::any) override;
  std::any tokenString(std::any) override;
  std::any tokenRegexp(std::any) override;
  std::any onActionRule(std::any, std::any) override;
  std::any onActionArg(std::any) override;
  std::any onArgs(std::any) override;
  std::any appendArgs(std::any, std::any) override;
  std::any onArg(std::any) override;

 private:
  void putCpp(const Rules& rules);
};
