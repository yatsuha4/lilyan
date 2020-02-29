/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "Grammer.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
class Parser
  : public Grammer
{
 public:
  Parser() = default;
  ~Parser() override = default;

  std::any parse(const std::string& text);

 protected:
  std::any onAdd(const std::any&, const std::any&) override;
  std::any onSub(const std::any&, const std::any&) override;
  std::any onMul(const std::any&, const std::any&) override;
  std::any onDiv(const std::any&, const std::any&) override;
  std::any onNumber(const std::smatch&) override;
  std::any onMinus(const std::any&) override;
};
