#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  bool rules(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule(r); }, &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onRules", [this, _args]() { return onRules(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool rule(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(getToken(std::regex(R"(\w+)"), &_args.at(0)) &&
         getToken(std::string(":")) &&
         isMatch(lilyan::Repeat::One, [this](std::any* r) { return semantics(r); }, &_args.at(1)) &&
         getToken(std::string(";"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onRule", [this, _args]() { return onRule(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool semantics(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return semantic(r); }, &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onSemantics", [this, _args]() { return onSemantics(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool semantic(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(isMatch(lilyan::Repeat::One, [this](std::any* r) { return tokens(r); }, &_args.at(0)) &&
         getToken(std::string("->")) &&
         isMatch(lilyan::Repeat::One, [this](std::any* r) { return action(r); }, &_args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onSemantic", [this, _args]() { return onSemantic(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool tokens(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return token(r); }, &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onTokens", [this, _args]() { return onTokens(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool token(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(getToken(std::regex(R"(\w+)"), &_args.at(0)) &&
         isMatch(lilyan::Repeat::ZeroOne, [this](std::any* r) { return token_r(r); }, &_args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenRule", [this, _args]() { return tokenRule(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("''"), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("\"\""), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("//"), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("tokenRegexp", [this, _args]() { return tokenRegexp(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool token_r(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("?"), &_args.at(0))) {
        setMatch(match, _args.at(0));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("*"), &_args.at(0))) {
        setMatch(match, _args.at(0));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string("+"), &_args.at(0))) {
        setMatch(match, _args.at(0));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool action(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(getToken(std::regex(R"(\w+)"), &_args.at(0)) &&
         getToken(std::string("(")) &&
         isMatch(lilyan::Repeat::One, [this](std::any* r) { return args(r); }, &_args.at(1)) &&
         getToken(std::string(")"))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionRule", [this, _args]() { return onActionRule(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    {
      std::array<std::any, 1> _args;
      if(isMatch(lilyan::Repeat::One, [this](std::any* r) { return arg(r); }, &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onActionArg", [this, _args]() { return onActionArg(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool args(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 2> _args;
      if(isMatch(lilyan::Repeat::One, [this](std::any* r) { return arg(r); }, &_args.at(0)) &&
         isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return args_r(r); }, &_args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onArgs", [this, _args]() { return onArgs(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool args_r(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(getToken(std::string(",")) &&
         isMatch(lilyan::Repeat::One, [this](std::any* r) { return arg(r); }, &_args.at(0))) {
        setMatch(match, _args.at(0));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
  bool arg(std::any* result = nullptr) {
    Match match;
    lilyan::Input _input(getInput());
    {
      std::array<std::any, 1> _args;
      if(getToken(std::regex(R"(\$(\d+))"), &_args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onArg", [this, _args]() { return onArg(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyMatch(match, result);
  }
 protected:
  Grammer() = default;
  ~Grammer() override = default;
  virtual std::any onRules(const std::any&) = 0;
  virtual std::any onRule(const std::any&, const std::any&) = 0;
  virtual std::any onSemantics(const std::any&) = 0;
  virtual std::any onSemantic(const std::any&, const std::any&) = 0;
  virtual std::any onTokens(const std::any&) = 0;
  virtual std::any tokenRule(const std::any&, const std::any&) = 0;
  virtual std::any tokenString(const std::any&) = 0;
  virtual std::any tokenRegexp(const std::any&) = 0;
  virtual std::any onActionRule(const std::any&, const std::any&) = 0;
  virtual std::any onActionArg(const std::any&) = 0;
  virtual std::any onArgs(const std::any&, const std::any&) = 0;
  virtual std::any onArg(const std::any&) = 0;
};
