#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  bool rule_main(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::any arg;
      if(isMatch(lilyan::Repeat::ZeroAny, [this](std::any* r) { return rule_expr(r); }, &arg)) {
        setMatch(match, arg);
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
  bool rule_expr(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::any arg;
      if(rule_term(&arg)) {
        setMatch(match, arg);
      }
      getInput() = input;
    }
    if(applyMatch(match, result)) {
      rule_expr(*match.value, result);
      return true;
    }
    return false;
  }
  void rule_expr(const std::any& value, std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if((static_cast<void>(args.at(0) = value), true) &&
         getToken(std::string("+")) &&
         rule_term(&args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onAdd", [this, args]() { return onAdd(eval(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 2> args;
      if((static_cast<void>(args.at(0) = value), true) &&
         getToken(std::string("-")) &&
         rule_term(&args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onSub", [this, args]() { return onSub(eval(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    if(applyMatch(match, result)) {
      rule_expr(*match.value, result);
    }
  }
  bool rule_term(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::any arg;
      if(rule_number(&arg)) {
        setMatch(match, arg);
      }
      getInput() = input;
    }
    if(applyMatch(match, result)) {
      rule_term(*match.value, result);
      return true;
    }
    return false;
  }
  void rule_term(const std::any& value, std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 2> args;
      if((static_cast<void>(args.at(0) = value), true) &&
         getToken(std::string("*")) &&
         rule_number(&args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onMul", [this, args]() { return onMul(eval(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    {
      std::array<std::any, 2> args;
      if((static_cast<void>(args.at(0) = value), true) &&
         getToken(std::string("/")) &&
         rule_number(&args.at(1))) {
        setMatch(match, std::make_shared<lilyan::Action>("onDiv", [this, args]() { return onDiv(eval(args.at(0)), eval(args.at(1))); }));
      }
      getInput() = input;
    }
    if(applyMatch(match, result)) {
      rule_term(*match.value, result);
    }
  }
  bool rule_number(std::any* result = nullptr) {
    Match match;
    lilyan::Input input(getInput());
    {
      std::array<std::any, 1> args;
      if(getToken(std::regex(R"(\d+)"), &args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onNumber", [this, args]() { return onNumber(std::any_cast<std::smatch>(args.at(0))); }));
      }
      getInput() = input;
    }
    {
      std::any arg;
      if(getToken(std::string("(")) &&
         rule_expr(&arg) &&
         getToken(std::string(")"))) {
        setMatch(match, arg);
      }
      getInput() = input;
    }
    {
      std::array<std::any, 1> args;
      if(getToken(std::string("-")) &&
         rule_expr(&args.at(0))) {
        setMatch(match, std::make_shared<lilyan::Action>("onMinus", [this, args]() { return onMinus(eval(args.at(0))); }));
      }
      getInput() = input;
    }
    return applyMatch(match, result);
  }
 protected:
  Grammer() = default;
  ~Grammer() override = default;
  virtual std::any onAdd(const std::any&, const std::any&) = 0;
  virtual std::any onSub(const std::any&, const std::any&) = 0;
  virtual std::any onMul(const std::any&, const std::any&) = 0;
  virtual std::any onDiv(const std::any&, const std::any&) = 0;
  virtual std::any onNumber(const std::smatch&) = 0;
  virtual std::any onMinus(const std::any&) = 0;
};
