#include "lilyan/lilyan.hpp"
class Parser : public lilyan::Parser {
 public:
  std::any main(lilyan::Input& input) {
    std::cerr << "main" << std::endl;
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, expr(_input))) {
        std::cerr << "onMainExpr" << std::endl;
        input = _input;
        return checkValue(onMainExpr(semantic[1]));
      }
    }
    return std::any();
  }
  std::any expr(lilyan::Input& input) {
    std::cerr << "expr" << std::endl;
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, number(_input)) &&
         append(semantic, _input, _input.match(std::string("+"))) &&
         append(semantic, _input, number(_input))) {
        std::cerr << "onAdd" << std::endl;
        input = _input;
        return checkValue(onAdd(semantic[1], semantic[3]));
      }
    }
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, number(_input)) &&
         append(semantic, _input, _input.match(std::string("-"))) &&
         append(semantic, _input, number(_input))) {
        std::cerr << "onSub" << std::endl;
        input = _input;
        return checkValue(onSub(semantic[1], semantic[3]));
      }
    }
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, number(_input))) {
        std::cerr << "onExpr" << std::endl;
        input = _input;
        return checkValue(onExpr(semantic[1]));
      }
    }
    return std::any();
  }
  std::any term(lilyan::Input& input) {
    std::cerr << "term" << std::endl;
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, term(_input)) &&
         append(semantic, _input, _input.match(std::string("*"))) &&
         append(semantic, _input, number(_input))) {
        std::cerr << "onMul" << std::endl;
        input = _input;
        return checkValue(onMul(semantic[1], semantic[3]));
      }
    }
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, term(_input)) &&
         append(semantic, _input, _input.match(std::string("/"))) &&
         append(semantic, _input, number(_input))) {
        std::cerr << "onDiv" << std::endl;
        input = _input;
        return checkValue(onDiv(semantic[1], semantic[3]));
      }
    }
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, number(_input))) {
        std::cerr << "onTerm" << std::endl;
        input = _input;
        return checkValue(onTerm(semantic[1]));
      }
    }
    return std::any();
  }
  std::any number(lilyan::Input& input) {
    std::cerr << "number" << std::endl;
    {
      lilyan::Input _input(input);
      lilyan::Semantic semantic;
      if(append(semantic, _input, _input.matchRegex(std::string(R"(\d+)")))) {
        std::cerr << "onNumber" << std::endl;
        input = _input;
        return checkValue(onNumber(semantic[1]));
      }
    }
    return std::any();
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
};
