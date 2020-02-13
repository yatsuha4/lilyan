#include "lilyan/lilyan.hpp"
class Parser : public lilyan::Parser {
 public:
  std::any rules(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      std::any result;
      if((result = rule(_input)).has_value()) {
        input = _input;
        return rules(input, result);
      }
    }
    return rules(input, std::any());
  }
  std::any rules(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      std::any result;
      if((result = value).has_value() &&
         rule(_input).has_value()) {
        input = _input;
        return rules(input, result);
      }
    }
    return value;
  }
  std::any rule(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if((result->at(1) = getToken(_input, std::regex(R"(\w+)"))).has_value() &&
         getToken(_input, std::string(":")).has_value() &&
         (result->at(2) = semantics(_input)).has_value() &&
         getToken(_input, std::string(";")).has_value()) {
        result->at(0) = Action("appendRule", static_cast<action_t>(&Parser::appendRule));
        input = _input;
        return result;
      }
    }
    return std::any();
  }
  std::any semantics(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = semantic(_input)).has_value()) {
        result->at(0) = Action("onSemantics", static_cast<action_t>(&Parser::onSemantics));
        input = _input;
        return semantics(input, result);
      }
    }
    return semantics(input, std::any());
  }
  std::any semantics(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if((result->at(1) = value).has_value() &&
         (result->at(2) = semantic(_input)).has_value()) {
        result->at(0) = Action("appendSemantics", static_cast<action_t>(&Parser::appendSemantics));
        input = _input;
        return semantics(input, result);
      }
    }
    return value;
  }
  std::any semantic(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if((result->at(1) = tokens(_input)).has_value() &&
         getToken(_input, std::string("->")).has_value() &&
         (result->at(2) = action(_input)).has_value()) {
        result->at(0) = Action("onSemantic", static_cast<action_t>(&Parser::onSemantic));
        input = _input;
        return result;
      }
    }
    return std::any();
  }
  std::any tokens(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = token(_input)).has_value()) {
        result->at(0) = Action("onTokens", static_cast<action_t>(&Parser::onTokens));
        input = _input;
        return tokens(input, result);
      }
    }
    return tokens(input, std::any());
  }
  std::any tokens(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if((result->at(1) = value).has_value() &&
         (result->at(2) = token(_input)).has_value()) {
        result->at(0) = Action("appendTokens", static_cast<action_t>(&Parser::appendTokens));
        input = _input;
        return tokens(input, result);
      }
    }
    return value;
  }
  std::any token(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(_input, std::regex(R"(\w+)"))).has_value()) {
        result->at(0) = Action("tokenRule", static_cast<action_t>(&Parser::tokenRule));
        input = _input;
        return result;
      }
    }
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(_input, std::string("''"))).has_value()) {
        result->at(0) = Action("tokenString", static_cast<action_t>(&Parser::tokenString));
        input = _input;
        return result;
      }
    }
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(_input, std::string(""""))).has_value()) {
        result->at(0) = Action("tokenString", static_cast<action_t>(&Parser::tokenString));
        input = _input;
        return result;
      }
    }
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(_input, std::string("//"))).has_value()) {
        result->at(0) = Action("tokenRegexp", static_cast<action_t>(&Parser::tokenRegexp));
        input = _input;
        return result;
      }
    }
    return std::any();
  }
  std::any action(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if((result->at(1) = getToken(_input, std::regex(R"(\w+)"))).has_value() &&
         getToken(_input, std::string("(")).has_value() &&
         (result->at(2) = args(_input)).has_value() &&
         getToken(_input, std::string(")")).has_value()) {
        result->at(0) = Action("onActionRule", static_cast<action_t>(&Parser::onActionRule));
        input = _input;
        return result;
      }
    }
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = arg(_input)).has_value()) {
        result->at(0) = Action("onActionArg", static_cast<action_t>(&Parser::onActionArg));
        input = _input;
        return result;
      }
    }
    return std::any();
  }
  std::any args(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = arg(_input)).has_value()) {
        result->at(0) = Action("onArgs", static_cast<action_t>(&Parser::onArgs));
        input = _input;
        return args(input, result);
      }
    }
    return args(input, std::any());
  }
  std::any args(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if((result->at(1) = value).has_value() &&
         getToken(_input, std::string(",")).has_value() &&
         (result->at(2) = arg(_input)).has_value()) {
        result->at(0) = Action("appendArgs", static_cast<action_t>(&Parser::appendArgs));
        input = _input;
        return args(input, result);
      }
    }
    return value;
  }
  std::any arg(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if((result->at(1) = getToken(_input, std::regex(R"(\$\d+)"))).has_value()) {
        result->at(0) = Action("onArg", static_cast<action_t>(&Parser::onArg));
        input = _input;
        return result;
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
