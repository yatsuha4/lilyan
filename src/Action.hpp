/***********************************************************************//**
	@file
***************************************************************************/
#pragma once
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action {
 private:
  std::string name_;
  std::vector<int> args_;

 public:
  Action(const std::string& name, const std::vector<int>& args);
  Action(const std::vector<int>& args);
  ~Action() = default;

  const auto& getName() const {
    return name_;
  }

  const auto& getArgs() const {
    return args_;
  }

  std::string toString() const;

  std::string prematch() const;
  std::string match(size_t index, const Rule& rule, const Token& token) const;
  std::string postmatch(Parser& parser) const;

 private:
  bool hasFunc() const;
  std::string argsToString() const;
};
