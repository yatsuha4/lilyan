#include "lilyan/lilyan.hpp"
class Parser : public lilyan::Parser {
 public:
  std::any main(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, expr(_input))) {
        std::cerr << "onMainExpr" << std::endl;
        input = _input;
        return checkValue(onMainExpr(semantic[1]));
      }
    }
    return checkValue(std::any());
  }
  std::any expr(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, term(_input))) {
        std::cerr << "onExpr" << std::endl;
        input = _input;
        return expr(input, checkValue(onExpr(semantic[1])));
      }
    }
    return expr(input, checkValue(std::any()));
  }
  std::any expr(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, value) &&
         append(semantic, _input, _input.match(std::string("+"))) &&
         append(semantic, _input, term(_input))) {
        std::cerr << "onAdd" << std::endl;
        input = _input;
        return expr(input, checkValue(onAdd(semantic[1], semantic[3])));
      }
    }
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, value) &&
         append(semantic, _input, _input.match(std::string("-"))) &&
         append(semantic, _input, term(_input))) {
        std::cerr << "onSub" << std::endl;
        input = _input;
        return expr(input, checkValue(onSub(semantic[1], semantic[3])));
      }
    }
    return value;
  }
  std::any term(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, number(_input))) {
        std::cerr << "onTerm" << std::endl;
        input = _input;
        return term(input, checkValue(onTerm(semantic[1])));
      }
    }
    return term(input, checkValue(std::any()));
  }
  std::any term(lilyan::Input& input, const std::any& value) {
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, value) &&
         append(semantic, _input, _input.match(std::string("*"))) &&
         append(semantic, _input, number(_input))) {
        std::cerr << "onMul" << std::endl;
        input = _input;
        return term(input, checkValue(onMul(semantic[1], semantic[3])));
      }
    }
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, value) &&
         append(semantic, _input, _input.match(std::string("/"))) &&
         append(semantic, _input, number(_input))) {
        std::cerr << "onDiv" << std::endl;
        input = _input;
        return term(input, checkValue(onDiv(semantic[1], semantic[3])));
      }
    }
    return value;
  }
  std::any number(lilyan::Input& input) {
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, _input.matchRegex(std::string(R"(\d+)")))) {
        std::cerr << "onNumber" << std::endl;
        input = _input;
        return checkValue(onNumber(semantic[1]));
      }
    }
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, _input.match(std::string("("))) &&
         append(semantic, _input, expr(_input)) &&
         append(semantic, _input, _input.match(std::string(")")))) {
        std::cerr << "toValue" << std::endl;
        input = _input;
        return checkValue(toValue(semantic[2]));
      }
    }
    return checkValue(std::any());
  }
 protected:
  Parser() = default;
  virtual ~Parser() = default;
  virtual std::any onMainExpr(const std::any&) = 0;
  virtual std::any onAdd(const std::any&, const std::any&) = 0;
  virtual std::any onSub(const std::any&, const std::any&) = 0;
  virtual std::any onExpr(const std::any&) = 0;
  virtual std::any onMul(const std::any&, const std::any&) = 0;
  virtual std::any onDiv(const std::any&, const std::any&) = 0;
  virtual std::any onTerm(const std::any&) = 0;
  virtual std::any onNumber(const std::any&) = 0;
  virtual std::any toValue(const std::any&) = 0;
};
