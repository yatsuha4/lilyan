#include "lilyan/lilyan.hpp"
class Parser : public lilyan::Parser {
 public:
  std::any main(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      std::any result;
      if(skip(_input) && (result = expr(_input)).has_value()) {
        input = _input;
        return result;
      }
    }
    return std::any();
  }
  std::any expr(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      std::any result;
      if(skip(_input) && (result = term(_input)).has_value()) {
        input = _input;
        return expr(input, result);
      }
    }
    return expr(input, std::any());
  }
  std::any expr(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if(skip(_input) && (result->at(1) = value).has_value() &&
         skip(_input) && _input.match(std::string("+")).has_value() &&
         skip(_input) && (result->at(2) = term(_input)).has_value()) {
        result->at(0) = Func("onAdd", static_cast<func_t>(&Parser::onAdd));
        input = _input;
        return expr(input, result);
      }
    }
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if(skip(_input) && (result->at(1) = value).has_value() &&
         skip(_input) && _input.match(std::string("-")).has_value() &&
         skip(_input) && (result->at(2) = term(_input)).has_value()) {
        result->at(0) = Func("onSub", static_cast<func_t>(&Parser::onSub));
        input = _input;
        return expr(input, result);
      }
    }
    return value;
  }
  std::any term(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      std::any result;
      if(skip(_input) && (result = number(_input)).has_value()) {
        input = _input;
        return term(input, result);
      }
    }
    return term(input, std::any());
  }
  std::any term(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if(skip(_input) && (result->at(1) = value).has_value() &&
         skip(_input) && _input.match(std::string("*")).has_value() &&
         skip(_input) && (result->at(2) = number(_input)).has_value()) {
        result->at(0) = Func("onMul", static_cast<func_t>(&Parser::onMul));
        input = _input;
        return term(input, result);
      }
    }
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(3);
      if(skip(_input) && (result->at(1) = value).has_value() &&
         skip(_input) && _input.match(std::string("/")).has_value() &&
         skip(_input) && (result->at(2) = number(_input)).has_value()) {
        result->at(0) = Func("onDiv", static_cast<func_t>(&Parser::onDiv));
        input = _input;
        return term(input, result);
      }
    }
    return value;
  }
  std::any number(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      auto result = std::make_shared<List>(2);
      if(skip(_input) && (result->at(1) = _input.match(std::regex(R"(\d+)"))).has_value()) {
        result->at(0) = Func("onNumber", static_cast<func_t>(&Parser::onNumber));
        input = _input;
        return result;
      }
    }
    {
      lilyan::Input _input(input);
      std::any result;
      if(skip(_input) && _input.match(std::string("(")).has_value() &&
         skip(_input) && (result = expr(_input)).has_value() &&
         skip(_input) && _input.match(std::string(")")).has_value()) {
        input = _input;
        return result;
      }
    }
    return std::any();
  }
 protected:
  Parser() = default;
  virtual ~Parser() = default;
  virtual std::any onAdd(const List& args) = 0;
  virtual std::any onSub(const List& args) = 0;
  virtual std::any onMul(const List& args) = 0;
  virtual std::any onDiv(const List& args) = 0;
  virtual std::any onNumber(const List& args) = 0;
};
