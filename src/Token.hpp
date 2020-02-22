/***********************************************************************//**
	@file
***************************************************************************/
#pragma once
/***********************************************************************//**
	@brief トークン
***************************************************************************/
class Token {
 public:
  class Regexp;
  class Rule;
  class String;

 private:
  std::string value_;

 public:
  Token(const std::string& value) : value_(value) {}
  virtual ~Token() = default;

  const auto& getValue() const {
    return value_;
  }

  virtual std::string toString() const;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Token::Regexp
  : public Token
{
 public:
  Regexp(const std::string& value) : Token(value) {}
  ~Regexp() override = default;

  std::string toString() const override;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Token::Rule
  : public Token
{
 public:
  Rule(const std::string& value) : Token(value) {}
  ~Rule() override = default;

  std::string toString() const override;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Token::String
  : public Token
{
 public:
  String(const std::string& value) : Token(value) {}
  ~String() override = default;

  std::string toString() const override;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
class Tokens
  : public std::vector<std::shared_ptr<Token>>
{
  using super = std::vector<std::shared_ptr<Token>>;

 public:
  Tokens() = default;
  ~Tokens() = default;

  std::string toString() const;
};
