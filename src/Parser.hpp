/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "Grammer.hpp"
#include "Output.hpp"
#include "Action.hpp"
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
  std::vector<std::shared_ptr<Action::Func>> actionFuncs_;

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
  std::any onRule(const std::smatch&, const std::any&) override;
  std::any onSemantics(const std::any&) override;
  std::any onSemantic(const std::any&, const std::any&) override;
  std::any onTokens(const std::any&) override;
  std::any tokenRule(const std::smatch&, const std::any&) override;
  std::any tokenString(const std::string&) override;
  std::any tokenRegexp(const std::string&) override;
  std::any onActionRule(const std::smatch&, const std::any&) override;
  std::any onActionConst(const std::smatch&) override;
  std::any onActionArg(const std::any&) override;
  std::any onArgs(const std::any&, const std::any&) override;
  std::any onArg(const std::smatch&) override;

 private:
  void putCpp(const Rules& rules);
};
