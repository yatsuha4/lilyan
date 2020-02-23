#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  std::any rules() {
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = rule()).has_value()) {
        return rules(std::make_shared<lilyan::Action>("onRules", std::bind(&Grammer::onRules, this, _args.at(0))));
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
        return rules(std::make_shared<lilyan::Action>("appendRules", std::bind(&Grammer::appendRules, this, _args.at(0), _args.at(1))));
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
        return std::make_shared<lilyan::Action>("onRule", std::bind(&Grammer::onRule, this, _args.at(0), _args.at(1)));
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
        return semantics(std::make_shared<lilyan::Action>("onSemantics", std::bind(&Grammer::onSemantics, this, _args.at(0))));
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
        return semantics(std::make_shared<lilyan::Action>("appendSemantics", std::bind(&Grammer::appendSemantics, this, _args.at(0), _args.at(1))));
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
        return std::make_shared<lilyan::Action>("onSemantic", std::bind(&Grammer::onSemantic, this, _args.at(0), _args.at(1)));
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
        return tokens(std::make_shared<lilyan::Action>("onTokens", std::bind(&Grammer::onTokens, this, _args.at(0))));
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
        return tokens(std::make_shared<lilyan::Action>("appendTokens", std::bind(&Grammer::appendTokens, this, _args.at(0), _args.at(1))));
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
        return std::make_shared<lilyan::Action>("tokenRule", std::bind(&Grammer::tokenRule, this, _args.at(0)));
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("''"))).has_value()) {
        return std::make_shared<lilyan::Action>("tokenString", std::bind(&Grammer::tokenString, this, _args.at(0)));
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("\"\""))).has_value()) {
        return std::make_shared<lilyan::Action>("tokenString", std::bind(&Grammer::tokenString, this, _args.at(0)));
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("//"))).has_value()) {
        return std::make_shared<lilyan::Action>("tokenRegexp", std::bind(&Grammer::tokenRegexp, this, _args.at(0)));
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
        return std::make_shared<lilyan::Action>("onActionRule", std::bind(&Grammer::onActionRule, this, _args.at(0), _args.at(1)));
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = arg()).has_value()) {
        return std::make_shared<lilyan::Action>("onActionArg", std::bind(&Grammer::onActionArg, this, _args.at(0)));
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
        return args(std::make_shared<lilyan::Action>("onArgs", std::bind(&Grammer::onArgs, this, _args.at(0))));
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
        return args(std::make_shared<lilyan::Action>("appendArgs", std::bind(&Grammer::appendArgs, this, _args.at(0), _args.at(1))));
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
        return std::make_shared<lilyan::Action>("onArg", std::bind(&Grammer::onArg, this, _args.at(0)));
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
  virtual std::any onRules(std::any) = 0;
  virtual std::any appendRules(std::any, std::any) = 0;
  virtual std::any onRule(std::any, std::any) = 0;
  virtual std::any onSemantics(std::any) = 0;
  virtual std::any appendSemantics(std::any, std::any) = 0;
  virtual std::any onSemantic(std::any, std::any) = 0;
  virtual std::any onTokens(std::any) = 0;
  virtual std::any appendTokens(std::any, std::any) = 0;
  virtual std::any tokenRule(std::any) = 0;
  virtual std::any tokenString(std::any) = 0;
  virtual std::any tokenRegexp(std::any) = 0;
  virtual std::any onActionRule(std::any, std::any) = 0;
  virtual std::any onActionArg(std::any) = 0;
  virtual std::any onArgs(std::any) = 0;
  virtual std::any appendArgs(std::any, std::any) = 0;
  virtual std::any onArg(std::any) = 0;
};
