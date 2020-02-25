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

  std::any onRules(const std::any&) override;
  std::any onRule(const std::any&, const std::any&) override;
  std::any onSemantics(const std::any&) override;
  std::any onSemantic(const std::any&, const std::any&) override;
  std::any onTokens(const std::any&) override;
  std::any tokenRule(const std::any&) override;
  std::any tokenString(const std::any&) override;
  std::any tokenRegexp(const std::any&) override;
  std::any onActionRule(const std::any&, const std::any&) override;
  std::any onActionArg(const std::any&) override;
  std::any onArgs(const std::any&) override;
  std::any appendArgs(const std::any&, const std::any&) override;
  std::any onArg(const std::any&) override;

 private:
  void putCpp(const Rules& rules);
};
