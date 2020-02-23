#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  std::any rules() {
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = rule()).has_value()) {
        result->at(0) = lilyan::Action("onRules", static_cast<lilyan::Action::Func>(&Grammer::onRules));
        return rules(result);
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
      auto result = std::make_shared<lilyan::List>(3);
      if((result->at(1) = value).has_value() &&
         (result->at(2) = rule()).has_value()) {
        result->at(0) = lilyan::Action("appendRules", static_cast<lilyan::Action::Func>(&Grammer::appendRules));
        return rules(result);
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
      auto result = std::make_shared<lilyan::List>(3);
      if((result->at(1) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string(":")).has_value() &&
         (result->at(2) = semantics()).has_value() &&
         getToken(std::string(";")).has_value()) {
        result->at(0) = lilyan::Action("onRule", static_cast<lilyan::Action::Func>(&Grammer::onRule));
        return result;
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
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = semantic()).has_value()) {
        result->at(0) = lilyan::Action("onSemantics", static_cast<lilyan::Action::Func>(&Grammer::onSemantics));
        return semantics(result);
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
      auto result = std::make_shared<lilyan::List>(3);
      if((result->at(1) = value).has_value() &&
         (result->at(2) = semantic()).has_value()) {
        result->at(0) = lilyan::Action("appendSemantics", static_cast<lilyan::Action::Func>(&Grammer::appendSemantics));
        return semantics(result);
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
      auto result = std::make_shared<lilyan::List>(3);
      if((result->at(1) = tokens()).has_value() &&
         getToken(std::string("->")).has_value() &&
         (result->at(2) = action()).has_value()) {
        result->at(0) = lilyan::Action("onSemantic", static_cast<lilyan::Action::Func>(&Grammer::onSemantic));
        return result;
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
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = token()).has_value()) {
        result->at(0) = lilyan::Action("onTokens", static_cast<lilyan::Action::Func>(&Grammer::onTokens));
        return tokens(result);
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
      auto result = std::make_shared<lilyan::List>(3);
      if((result->at(1) = value).has_value() &&
         (result->at(2) = token()).has_value()) {
        result->at(0) = lilyan::Action("appendTokens", static_cast<lilyan::Action::Func>(&Grammer::appendTokens));
        return tokens(result);
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
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = getToken(std::regex(R"(\w+)"))).has_value()) {
        result->at(0) = lilyan::Action("tokenRule", static_cast<lilyan::Action::Func>(&Grammer::tokenRule));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = getToken(std::string("''"))).has_value()) {
        result->at(0) = lilyan::Action("tokenString", static_cast<lilyan::Action::Func>(&Grammer::tokenString));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = getToken(std::string("\"\""))).has_value()) {
        result->at(0) = lilyan::Action("tokenString", static_cast<lilyan::Action::Func>(&Grammer::tokenString));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = getToken(std::string("//"))).has_value()) {
        result->at(0) = lilyan::Action("tokenRegexp", static_cast<lilyan::Action::Func>(&Grammer::tokenRegexp));
        return result;
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
      auto result = std::make_shared<lilyan::List>(3);
      if((result->at(1) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string("(")).has_value() &&
         (result->at(2) = args()).has_value() &&
         getToken(std::string(")")).has_value()) {
        result->at(0) = lilyan::Action("onActionRule", static_cast<lilyan::Action::Func>(&Grammer::onActionRule));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = arg()).has_value()) {
        result->at(0) = lilyan::Action("onActionArg", static_cast<lilyan::Action::Func>(&Grammer::onActionArg));
        return result;
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
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = arg()).has_value()) {
        result->at(0) = lilyan::Action("onArgs", static_cast<lilyan::Action::Func>(&Grammer::onArgs));
        return args(result);
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
      auto result = std::make_shared<lilyan::List>(3);
      if((result->at(1) = value).has_value() &&
         getToken(std::string(",")).has_value() &&
         (result->at(2) = arg()).has_value()) {
        result->at(0) = lilyan::Action("appendArgs", static_cast<lilyan::Action::Func>(&Grammer::appendArgs));
        return args(result);
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
      auto result = std::make_shared<lilyan::List>(2);
      if((result->at(1) = getToken(std::regex(R"(\$(\d+))"))).has_value()) {
        result->at(0) = lilyan::Action("onArg", static_cast<lilyan::Action::Func>(&Grammer::onArg));
        return result;
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
  virtual std::any onRules(const lilyan::List& args) = 0;
  virtual std::any appendRules(const lilyan::List& args) = 0;
  virtual std::any onRule(const lilyan::List& args) = 0;
  virtual std::any onSemantics(const lilyan::List& args) = 0;
  virtual std::any appendSemantics(const lilyan::List& args) = 0;
  virtual std::any onSemantic(const lilyan::List& args) = 0;
  virtual std::any onTokens(const lilyan::List& args) = 0;
  virtual std::any appendTokens(const lilyan::List& args) = 0;
  virtual std::any tokenRule(const lilyan::List& args) = 0;
  virtual std::any tokenString(const lilyan::List& args) = 0;
  virtual std::any tokenRegexp(const lilyan::List& args) = 0;
  virtual std::any onActionRule(const lilyan::List& args) = 0;
  virtual std::any onActionArg(const lilyan::List& args) = 0;
  virtual std::any onArgs(const lilyan::List& args) = 0;
  virtual std::any appendArgs(const lilyan::List& args) = 0;
  virtual std::any onArg(const lilyan::List& args) = 0;
};
