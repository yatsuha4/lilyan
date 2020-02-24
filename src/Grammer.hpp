#include "lilyan/lilyan.hpp"
class Grammer : public lilyan::Parser {
 public:
  std::any rules() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = rule()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onRules", [this, _args]() { return onRules(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return rules(applyResult(result));
  }
  std::any rules(const std::any& value) {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         (_args.at(1) = rule()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("appendRules", [this, _args]() { return appendRules(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return result.value.has_value() ? rules(applyResult(result)) : value;
  }
  std::any rule() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string(":")).has_value() &&
         (_args.at(1) = semantics()).has_value() &&
         getToken(std::string(";")).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onRule", [this, _args]() { return onRule(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyResult(result);
  }
  std::any semantics() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = semantic()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onSemantics", [this, _args]() { return onSemantics(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return semantics(applyResult(result));
  }
  std::any semantics(const std::any& value) {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         (_args.at(1) = semantic()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("appendSemantics", [this, _args]() { return appendSemantics(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return result.value.has_value() ? semantics(applyResult(result)) : value;
  }
  std::any semantic() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = tokens()).has_value() &&
         getToken(std::string("->")).has_value() &&
         (_args.at(1) = action()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onSemantic", [this, _args]() { return onSemantic(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return applyResult(result);
  }
  std::any tokens() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = token()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onTokens", [this, _args]() { return onTokens(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return tokens(applyResult(result));
  }
  std::any tokens(const std::any& value) {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         (_args.at(1) = token()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("appendTokens", [this, _args]() { return appendTokens(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return result.value.has_value() ? tokens(applyResult(result)) : value;
  }
  std::any token() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::regex(R"((\w+)([\?\*\+])?)"))).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("tokenRule", [this, _args]() { return tokenRule(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("''"))).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("\"\""))).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("tokenString", [this, _args]() { return tokenString(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::string("//"))).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("tokenRegexp", [this, _args]() { return tokenRegexp(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyResult(result);
  }
  std::any action() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = getToken(std::regex(R"(\w+)"))).has_value() &&
         getToken(std::string("(")).has_value() &&
         (_args.at(1) = args()).has_value() &&
         getToken(std::string(")")).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onActionRule", [this, _args]() { return onActionRule(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = arg()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onActionArg", [this, _args]() { return onActionArg(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyResult(result);
  }
  std::any args() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = arg()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onArgs", [this, _args]() { return onArgs(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return args(applyResult(result));
  }
  std::any args(const std::any& value) {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 2> _args;
      if((_args.at(0) = value).has_value() &&
         getToken(std::string(",")).has_value() &&
         (_args.at(1) = arg()).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("appendArgs", [this, _args]() { return appendArgs(eval(_args.at(0)), eval(_args.at(1))); }));
      }
      getInput() = _input;
    }
    return result.value.has_value() ? args(applyResult(result)) : value;
  }
  std::any arg() {
    Result result;
    {
      lilyan::Input _input(getInput());
      std::array<std::any, 1> _args;
      if((_args.at(0) = getToken(std::regex(R"(\$(\d+))"))).has_value()) {
        setResult(result, std::make_shared<lilyan::Action>("onArg", [this, _args]() { return onArg(eval(_args.at(0))); }));
      }
      getInput() = _input;
    }
    return applyResult(result);
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
