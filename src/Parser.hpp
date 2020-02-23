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

  std::any onRules(const lilyan::List& args) override;
  std::any appendRules(const lilyan::List& args) override;
  std::any onRule(const lilyan::List& args) override;
  std::any onSemantics(const lilyan::List& args) override;
  std::any appendSemantics(const lilyan::List& args) override;
  std::any onSemantic(const lilyan::List& args) override;
  std::any onTokens(const lilyan::List& args) override;
  std::any appendTokens(const lilyan::List& args) override;
  std::any tokenRule(const lilyan::List& args) override;
  std::any tokenString(const lilyan::List& args) override;
  std::any tokenRegexp(const lilyan::List& args) override;
  std::any onActionRule(const lilyan::List& args) override;
  std::any onActionArg(const lilyan::List& args) override;
  std::any onArgs(const lilyan::List& args) override;
  std::any appendArgs(const lilyan::List& args) override;
  std::any onArg(const lilyan::List& args) override;

 private:
  void putCpp(const Rules& rules);
};
