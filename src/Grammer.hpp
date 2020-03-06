#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  bool rule_rules(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule_rule(r); }, &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onRules", [this, args]() { return onRules(eval(args.at(0))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_rule(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(getToken(std::regex(R"(\w+)"), &args.at(0)) &&
         getToken(std::string(":")) &&
         rule_semantics(&args.at(1)) &&
         getToken(std::string(";"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onRule", [this, args]() { return onRule(std::any_cast<std::smatch>(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_semantics(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return rule_semantic(r); }, &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onSemantics", [this, args]() { return onSemantics(eval(args.at(0))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_semantic(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(rule_tokens(&args.at(0)) &&
         getToken(std::string("->")) &&
         rule_action(&args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onSemantic", [this, args]() { return onSemantic(eval(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_tokens(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return rule_token(r); }, &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onTokens", [this, args]() { return onTokens(eval(args.at(0))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_token(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      if(getToken(std::string("<<EOF>>"))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenEof", [this]() { return tokenEof(); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 2> args;
      if(getToken(std::regex(R"(\w+)"), &args.at(0)) &&
         (rule_token_r(&args.at(1)) || true)) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenRule", [this, args]() { return tokenRule(std::any_cast<std::smatch>(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("''"), &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenString", [this, args]() { return tokenString(std::any_cast<std::string>(args.at(0))); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("\"\""), &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenString", [this, args]() { return tokenString(std::any_cast<std::string>(args.at(0))); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("//"), &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenRegexp", [this, args]() { return tokenRegexp(std::any_cast<std::string>(args.at(0))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_token_r(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      if(getToken(std::string("?"))) {
        setMatch(match, lilyan::Repeat::ZeroOne);
      }
      getInput() = input;
    }
    {
      if(getToken(std::string("*"))) {
        setMatch(match, lilyan::Repeat::ZeroAny);
      }
      getInput() = input;
    }
    {
      if(getToken(std::string("+"))) {
        setMatch(match, lilyan::Repeat::OneAny);
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_action(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(getToken(std::regex(R"(\w+)"), &args.at(0)) &&
         getToken(std::string("(")) &&
         (rule_args(&args.at(1)) || true) &&
         getToken(std::string(")"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionRule", [this, args]() { return onActionRule(std::any_cast<std::smatch>(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("<")) &&
         getToken(std::regex(R"([\w:]+)"), &args.at(0)) &&
         getToken(std::string(">"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionConst", [this, args]() { return onActionConst(std::any_cast<std::smatch>(args.at(0))); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(rule_arg(&args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionArg", [this, args]() { return onActionArg(eval(args.at(0))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_args(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(rule_arg(&args.at(0)) &&
         isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule_args_r(r); }, &args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onArgs", [this, args]() { return onArgs(eval(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_args_r(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::any arg;
      if(getToken(std::string(",")) &&
         rule_arg(&arg)) {
        setMatch(match, arg);
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_arg(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(getToken(std::regex(R"(\$(\d+))"), &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onArg", [this, args]() { return onArg(std::any_cast<std::smatch>(args.at(0))); }));
      }
      getInput() = input;
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
  virtual std::any tokenEof() = 0;
  virtual std::any tokenRule(const std::smatch&, const std::any&) = 0;
  virtual std::any tokenString(const std::string&) = 0;
  virtual std::any tokenRegexp(const std::string&) = 0;
  virtual std::any onActionRule(const std::smatch&, const std::any&) = 0;
  virtual std::any onActionConst(const std::smatch&) = 0;
  virtual std::any onActionArg(const std::any&) = 0;
  virtual std::any onArgs(const std::any&, const std::any&) = 0;
  virtual std::any onArg(const std::smatch&) = 0;
};
