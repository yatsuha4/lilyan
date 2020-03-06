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
  class Const;
  class Func;

 public:
  Action() = default;
  virtual ~Action() = default;

  virtual void prematch(Output& output) const = 0;
  virtual std::string match(size_t index, 
                            const Rule& rule, 
                            const Token& token) = 0;
  virtual std::string postmatch(Parser& parser) const = 0;

  std::string toString() const {
    return "";
  }

  static std::string GetArg(size_t index);
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

  void prematch(Output& output) const override;
  std::string match(size_t index, 
                    const Rule& rule, 
                    const Token& token) override;
  std::string postmatch(Parser& parser) const override;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action::Const
  : public Action
{
 private:
  std::string value_;

 public:
  Const(const std::string& value);
  ~Const() override = default;

  void prematch(Output& output) const override;
  std::string match(size_t index, 
                    const Rule& rule, 
                    const Token& token) override;
  std::string postmatch(Parser& parser) const override;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action::Func
  : public Action
{
 private:
  std::string name_;
  std::vector<int> args_;
  std::vector<std::type_index> types_;

 public:
  Func(const std::string& name, const std::vector<int>& args);
  ~Func() override = default;

  const auto& getName() const {
    return name_;
  }

  const auto& getArgs() const {
    return args_;
  }

  const auto& getTypes() const {
    return types_;
  }

  void prematch(Output& output) const override;
  std::string match(size_t index, 
                    const Rule& rule, 
                    const Token& token) override;
  std::string postmatch(Parser& parser) const override;

  void declare(Output& output) const;
};
