﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action {
 public:
  class Arg;
  class Func;

 public:
  Action() = default;
  virtual ~Action() = default;

  virtual std::string prematch() const = 0;
  virtual std::string match(size_t index, 
                            const Rule& rule, 
                            const Token& token) const = 0;
  virtual std::string postmatch(Parser& parser) const = 0;

  std::string toString() const {
    return "";
  }
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
/***********************************************************************//**
	@brief 
***************************************************************************/
class Action::Func
  : public Action
{
 private:
  std::string name_;
  std::vector<int> args_;

 public:
  Func(const std::string& name, const std::vector<int>& args);
  ~Func() override = default;

  const auto& getName() const {
    return name_;
  }

  const auto& getArgs() const {
    return args_;
  }

  std::string prematch() const override;
  std::string match(size_t index, 
                    const Rule& rule, 
                    const Token& token) const override;
  std::string postmatch(Parser& parser) const override;
};
