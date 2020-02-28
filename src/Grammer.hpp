#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  bool rule_rules(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule_rule(r); }, &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onRules", [this, _args]() { return onRules(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_rule(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(getToken(std::regex(R"(\w+)"), &_args.at(0)) &&
         getToken(std::string(":")) &&
         rule_semantics(&_args.at(1)) &&
         getToken(std::string(";"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onRule", [this, _args]() { return onRule(std::any_cast<std::smatch>(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_semantics(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return rule_semantic(r); }, &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onSemantics", [this, _args]() { return onSemantics(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_semantic(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(rule_tokens(&_args.at(0)) &&
         getToken(std::string("->")) &&
         rule_action(&_args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onSemantic", [this, _args]() { return onSemantic(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_tokens(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return rule_token(r); }, &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onTokens", [this, _args]() { return onTokens(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_token(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(getToken(std::regex(R"(\w+)"), &_args.at(0)) &&
         isMatch(lilyan::Repeat::ZeroOne, [this](std::any* r) { return rule_token_r(r); }, &_args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenRule", [this, _args]() { return tokenRule(std::any_cast<std::smatch>(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("''"), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(std::any_cast<std::string>(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("\"\""), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(std::any_cast<std::string>(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("//"), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenRegexp", [this, _args]() { return tokenRegexp(std::any_cast<std::string>(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_token_r(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      if(getToken(std::string("?"))) {
        setMatch(match, lilyan::Repeat::ZeroOne);
      }
      getInput() = _input;
    }
    {
      if(getToken(std::string("*"))) {
        setMatch(match, lilyan::Repeat::ZeroAny);
      }
      getInput() = _input;
    }
    {
      if(getToken(std::string("+"))) {
        setMatch(match, lilyan::Repeat::OneAny);
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_action(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(getToken(std::regex(R"(\w+)"), &_args.at(0)) &&
         getToken(std::string("(")) &&
         rule_args(&_args.at(1)) &&
         getToken(std::string(")"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionRule", [this, _args]() { return onActionRule(std::any_cast<std::smatch>(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("<")) &&
         getToken(std::regex(R"([\w:]+)"), &_args.at(0)) &&
         getToken(std::string(">"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionConst", [this, _args]() { return onActionConst(std::any_cast<std::smatch>(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(rule_arg(&_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionArg", [this, _args]() { return onActionArg(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_args(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(rule_arg(&_args.at(0)) &&
         isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule_args_r(r); }, &_args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onArgs", [this, _args]() { return onArgs(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_args_r(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::any _arg;
      if(getToken(std::string(",")) &&
         rule_arg(&_arg)) {
        setMatch(match, _arg);
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule_arg(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(getToken(std::regex(R"(\$(\d+))"), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onArg", [this, _args]() { return onArg(std::any_cast<std::smatch>(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
 protected:
  Grammer() = default;
  ~Grammer() override = default;
  virtual std::any onRules(const std::any&) = 0;
  virtual std::any onRule(const std::smatch&, const std::any&) = 0;
  virtual std::any onSemantics(const std::any&) = 0;
  virtual std::any onSemantic(const std::any&, const std::any&) = 0;
  virtual std::any onTokens(const std::any&) = 0;
  virtual std::any tokenRule(const std::smatch&, const std::any&) = 0;
  virtual std::any tokenString(const std::string&) = 0;
  virtual std::any tokenRegexp(const std::string&) = 0;
  virtual std::any onActionRule(const std::smatch&, const std::any&) = 0;
  virtual std::any onActionConst(const std::smatch&) = 0;
  virtual std::any onActionArg(const std::any&) = 0;
  virtual std::any onArgs(const std::any&, const std::any&) = 0;
  virtual std::any onArg(const std::smatch&) = 0;
};
