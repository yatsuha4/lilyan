#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  std::any rules() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = rule()).has_value()) {
        return rules(std::make_shared<lilyan::Action>("onRules", [this, _args]() { return onRules(eval(_args.at(0))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return rules(std::any());
  }
  std::any rules(const std::any& value) {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         (_args.at(1) = rule()).has_value()) {
        return rules(std::make_shared<lilyan::Action>("appendRules", [this, _args]() { return appendRules(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return value;
  }
  std::any rule() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string(":")).has_value() &&
         (_args.at(1) = semantics()).has_value() &&
         getToken(std::string(";")).has_value()) {
        return std::make_shared<lilyan::Action>("onRule", [this, _args]() { return onRule(eval(_args.at(0)), eval(_args.at(1))); });
      }
      else {
        getInput() = _input;
      }
    }
    return std::any();
  }
  std::any semantics() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = semantic()).has_value()) {
        return semantics(std::make_shared<lilyan::Action>("onSemantics", [this, _args]() { return onSemantics(eval(_args.at(0))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return semantics(std::any());
  }
  std::any semantics(const std::any& value) {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         (_args.at(1) = semantic()).has_value()) {
        return semantics(std::make_shared<lilyan::Action>("appendSemantics", [this, _args]() { return appendSemantics(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return value;
  }
  std::any semantic() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = tokens()).has_value() &&
         getToken(std::string("->")).has_value() &&
         (_args.at(1) = action()).has_value()) {
        return std::make_shared<lilyan::Action>("onSemantic", [this, _args]() { return onSemantic(eval(_args.at(0)), eval(_args.at(1))); });
      }
      else {
        getInput() = _input;
      }
    }
    return std::any();
  }
  std::any tokens() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = token()).has_value()) {
        return tokens(std::make_shared<lilyan::Action>("onTokens", [this, _args]() { return onTokens(eval(_args.at(0))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return tokens(std::any());
  }
  std::any tokens(const std::any& value) {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         (_args.at(1) = token()).has_value()) {
        return tokens(std::make_shared<lilyan::Action>("appendTokens", [this, _args]() { return appendTokens(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return value;
  }
  std::any token() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::regex(R"(\w+)"))).has_value()) {
        return std::make_shared<lilyan::Action>("tokenRule", [this, _args]() { return tokenRule(eval(_args.at(0))); });
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("''"))).has_value()) {
        return std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(eval(_args.at(0))); });
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("\"\""))).has_value()) {
        return std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(eval(_args.at(0))); });
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("//"))).has_value()) {
        return std::make_shared<lilyan::Action>("tokenRegexp", [this, _args]() { return tokenRegexp(eval(_args.at(0))); });
      }
      else {
        getInput() = _input;
      }
    }
    return std::any();
  }
  std::any action() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string("(")).has_value() &&
         (_args.at(1) = args()).has_value() &&
         getToken(std::string(")")).has_value()) {
        return std::make_shared<lilyan::Action>("onActionRule", [this, _args]() { return onActionRule(eval(_args.at(0)), eval(_args.at(1))); });
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = arg()).has_value()) {
        return std::make_shared<lilyan::Action>("onActionArg", [this, _args]() { return onActionArg(eval(_args.at(0))); });
      }
      else {
        getInput() = _input;
      }
    }
    return std::any();
  }
  std::any args() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = arg()).has_value()) {
        return args(std::make_shared<lilyan::Action>("onArgs", [this, _args]() { return onArgs(eval(_args.at(0))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return args(std::any());
  }
  std::any args(const std::any& value) {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         getToken(std::string(",")).has_value() &&
         (_args.at(1) = arg()).has_value()) {
        return args(std::make_shared<lilyan::Action>("appendArgs", [this, _args]() { return appendArgs(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      else {
        getInput() = _input;
      }
    }
    return value;
  }
  std::any arg() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::regex(R"(\$(\d+))"))).has_value()) {
        return std::make_shared<lilyan::Action>("onArg", [this, _args]() { return onArg(eval(_args.at(0))); });
      }
      else {
        getInput() = _input;
      }
    }
    return std::any();
  }
 protected:
  Grammer() = default;
  ~Grammer() override = default;
  virtual std::any onRules(const std::any&) = 0;
  virtual std::any appendRules(const std::any&, const std::any&) = 0;
  virtual std::any onRule(const std::any&, const std::any&) = 0;
  virtual std::any onSemantics(const std::any&) = 0;
  virtual std::any appendSemantics(const std::any&, const std::any&) = 0;
  virtual std::any onSemantic(const std::any&, const std::any&) = 0;
  virtual std::any onTokens(const std::any&) = 0;
  virtual std::any appendTokens(const std::any&, const std::any&) = 0;
  virtual std::any tokenRule(const std::any&) = 0;
  virtual std::any tokenString(const std::any&) = 0;
  virtual std::any tokenRegexp(const std::any&) = 0;
  virtual std::any onActionRule(const std::any&, const std::any&) = 0;
  virtual std::any onActionArg(const std::any&) = 0;
  virtual std::any onArgs(const std::any&) = 0;
  virtual std::any appendArgs(const std::any&, const std::any&) = 0;
  virtual std::any onArg(const std::any&) = 0;
};
