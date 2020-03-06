#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  bool rule_rules(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule_rule(r); }, &args.at(0)) &&
         isEof()) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onRules", [this, args]() { return onRules(args.at(0)); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_rule(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(getToken(std::regex(R"(\w+)"), &args.at(0)) &&
         getToken(std::string(":")) &&
         rule_semantics(&args.at(1)) &&
         getToken(std::string(";"))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onRule", [this, args]() { return onRule(std::any_cast<std::smatch>(args.at(0)), args.at(1)); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_semantics(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return rule_semantic(r); }, &args.at(0))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onSemantics", [this, args]() { return onSemantics(args.at(0)); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_semantic(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(rule_tokens(&args.at(0)) &&
         getToken(std::string("->")) &&
         rule_action(&args.at(1))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onSemantic", [this, args]() { return onSemantic(args.at(0), args.at(1)); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_tokens(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(isMatch(lilyan::Repeat::OneAny, [this](std::any* r) { return rule_token(r); }, &args.at(0))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onTokens", [this, args]() { return onTokens(args.at(0)); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_token(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      if(getToken(std::string("<<EOF>>"))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("tokenEof", [this]() { return tokenEof(); });
        }
        return true;
      }
      getInput() = input;
    }
    {
      std::array<std::any, 2> args;
      if(getToken(std::regex(R"(\w+)"), &args.at(0)) &&
         (rule_token_r(&args.at(1)) || true)) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("tokenRule", [this, args]() { return tokenRule(std::any_cast<std::smatch>(args.at(0)), args.at(1)); });
        }
        return true;
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("''"), &args.at(0))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("tokenString", [this, args]() { return tokenString(std::any_cast<std::string>(args.at(0))); });
        }
        return true;
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("\"\""), &args.at(0))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("tokenString", [this, args]() { return tokenString(std::any_cast<std::string>(args.at(0))); });
        }
        return true;
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("//"), &args.at(0))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("tokenRegexp", [this, args]() { return tokenRegexp(std::any_cast<std::string>(args.at(0))); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_token_r(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      if(getToken(std::string("?"))) {
        if(result) {
          *result = lilyan::Repeat::ZeroOne;
        }
        return true;
      }
      getInput() = input;
    }
    {
      if(getToken(std::string("*"))) {
        if(result) {
          *result = lilyan::Repeat::ZeroAny;
        }
        return true;
      }
      getInput() = input;
    }
    {
      if(getToken(std::string("+"))) {
        if(result) {
          *result = lilyan::Repeat::OneAny;
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_action(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(getToken(std::regex(R"(\w+)"), &args.at(0)) &&
         getToken(std::string("(")) &&
         (rule_args(&args.at(1)) || true) &&
         getToken(std::string(")"))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onActionRule", [this, args]() { return onActionRule(std::any_cast<std::smatch>(args.at(0)), args.at(1)); });
        }
        return true;
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("<")) &&
         getToken(std::regex(R"([\w:]+)"), &args.at(0)) &&
         getToken(std::string(">"))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onActionConst", [this, args]() { return onActionConst(std::any_cast<std::smatch>(args.at(0))); });
        }
        return true;
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(rule_arg(&args.at(0))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onActionArg", [this, args]() { return onActionArg(args.at(0)); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_args(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if(rule_arg(&args.at(0)) &&
         isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule_args_r(r); }, &args.at(1))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onArgs", [this, args]() { return onArgs(args.at(0), args.at(1)); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_args_r(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::any arg;
      if(getToken(std::string(",")) &&
         rule_arg(&arg)) {
        if(result) {
          *result = arg;
        }
        return true;
      }
      getInput() = input;
    }
    return false;
  }
  bool rule_arg(std::any* result = nullptr) {
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(getToken(std::regex(R"(\$(\d+))"), &args.at(0))) {
        if(result) {
          *result = std::make_shared<lilyan::Action>("onArg", [this, args]() { return onArg(std::any_cast<std::smatch>(args.at(0))); });
        }
        return true;
      }
      getInput() = input;
    }
    return false;
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
