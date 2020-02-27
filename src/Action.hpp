/***********************************************************************//**
	@file
***************************************************************************/
#pragma once
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action {
 public:
  class Arg;

 private:
  std::string name_;
  std::vector<int> args_;

 public:
  Action(const std::string& name, const std::vector<int>& args);
  Action(int arg);
  virtual ~Action() = default;

  const auto& getName() const {
    return name_;
  }

  const auto& getArgs() const {
    return args_;
  }

  std::string toString() const;

  virtual std::string prematch() const;
  virtual std::string match(size_t index, 
                            const Rule& rule, 
                            const Token& token) const;
  virtual std::string postmatch(Parser& parser) const;

 protected:
  Action() = default;

 private:
  bool hasFunc() const;
  std::string argsToString() const;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action::Arg
  : public Action
{
 private:
  int index_;

 public:
  Arg(int index);
  ~Arg() override = default;

  std::string prematch() const override;
  std::string match(size_t index, 
                    const Rule& rule, 
                    const Token& token) const override;
  std::string postmatch(Parser& parser) const override;
};
