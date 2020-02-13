#include "lilyan/lilyan.hpp"
class Parser : public lilyan::Parser {
 public:
  std::any rules() {
    {
      lilyan::Input _input(getInput());
      std::any result;
      if((result = rule()).has_value()) {
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
      std::any result;
      if((result = value).has_value() &&
         rule().has_value()) {
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
      auto result = std::make_shared<List>(3);
      if((result->at(1) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string(":")).has_value() &&
         (result->at(2) = semantics()).has_value() &&
         getToken(std::string(";")).has_value()) {
        result->at(0) = Action("appendRule", static_cast<action_t>(&Parser::appendRule));
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
      auto result = std::make_shared<List>(2);
      if((result->at(1) = semantic()).has_value()) {
        result->at(0) = Action("onSemantics", static_cast<action_t>(&Parser::onSemantics));
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
      auto result = std::make_shared<List>(3);
      if((result->at(1) = value).has_value() &&
         (result->at(2) = semantic()).has_value()) {
        result->at(0) = Action("appendSemantics", static_cast<action_t>(&Parser::appendSemantics));
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
      auto result = std::make_shared<List>(3);
      if((result->at(1) = tokens()).has_value() &&
         getToken(std::string("->")).has_value() &&
         (result->at(2) = action()).has_value()) {
        result->at(0) = Action("onSemantic", static_cast<action_t>(&Parser::onSemantic));
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
      auto result = std::make_shared<List>(2);
      if((result->at(1) = token()).has_value()) {
        result->at(0) = Action("onTokens", static_cast<action_t>(&Parser::onTokens));
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
      auto result = std::make_shared<List>(3);
      if((result->at(1) = value).has_value() &&
         (result->at(2) = token()).has_value()) {
        result->at(0) = Action("appendTokens", static_cast<action_t>(&Parser::appendTokens));
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
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(std::regex(R"(\w+)"))).has_value()) {
        result->at(0) = Action("tokenRule", static_cast<action_t>(&Parser::tokenRule));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(std::string("''"))).has_value()) {
        result->at(0) = Action("tokenString", static_cast<action_t>(&Parser::tokenString));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(std::string(""""))).has_value()) {
        result->at(0) = Action("tokenString", static_cast<action_t>(&Parser::tokenString));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(std::string("//"))).has_value()) {
        result->at(0) = Action("tokenRegexp", static_cast<action_t>(&Parser::tokenRegexp));
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
      auto result = std::make_shared<List>(3);
      if((result->at(1) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string("(")).has_value() &&
         (result->at(2) = args()).has_value() &&
         getToken(std::string(")")).has_value()) {
        result->at(0) = Action("onActionRule", static_cast<action_t>(&Parser::onActionRule));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    {
      lilyan::Input _input(getInput());
      auto result = std::make_shared<List>(2);
      if((result->at(1) = arg()).has_value()) {
        result->at(0) = Action("onActionArg", static_cast<action_t>(&Parser::onActionArg));
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
      auto result = std::make_shared<List>(2);
      if((result->at(1) = arg()).has_value()) {
        result->at(0) = Action("onArgs", static_cast<action_t>(&Parser::onArgs));
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
      auto result = std::make_shared<List>(3);
      if((result->at(1) = value).has_value() &&
         getToken(std::string(",")).has_value() &&
         (result->at(2) = arg()).has_value()) {
        result->at(0) = Action("appendArgs", static_cast<action_t>(&Parser::appendArgs));
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
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(std::regex(R"(\$\d+)"))).has_value()) {
        result->at(0) = Action("onArg", static_cast<action_t>(&Parser::onArg));
        return result;
      }
      else {
        getInput() = _input;
      }
    }
    return std::any();
  }
 protected:
  Parser() = default;
  virtual ~Parser() = default;
  virtual std::any appendRule(const List& args) = 0;
  virtual std::any onSemantics(const List& args) = 0;
  virtual std::any appendSemantics(const List& args) = 0;
  virtual std::any onSemantic(const List& args) = 0;
  virtual std::any onTokens(const List& args) = 0;
  virtual std::any appendTokens(const List& args) = 0;
  virtual std::any tokenRule(const List& args) = 0;
  virtual std::any tokenString(const List& args) = 0;
  virtual std::any tokenRegexp(const List& args) = 0;
  virtual std::any onActionRule(const List& args) = 0;
  virtual std::any onActionArg(const List& args) = 0;
  virtual std::any onArgs(const List& args) = 0;
  virtual std::any appendArgs(const List& args) = 0;
  virtual std::any onArg(const List& args) = 0;
};
