/***********************************************************************//**
	@file
***************************************************************************/
#include <iostream>
#include "Parser.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
class Main : public Parser {
 public:
  Main() = default;
  ~Main() override = default;

  std::any onMainExpr(const std::any& v1) override;
  std::any onExpr(const std::any& v1) override;
  std::any onAdd(const std::any& v1, const std::any& v2) override;
  std::any onSub(const std::any& v1, const std::any& v2) override;
  std::any onTerm(const std::any& v1) override;
  std::any onMul(const std::any& v1, const std::any& v2) override;
  std::any onDiv(const std::any& v1, const std::any& v2) override;
  std::any onNumber(const std::any& v1) override;
  std::any toValue(const std::any& v1) override {
    return v1;
  }
};
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onMainExpr(const std::any& v1) {
  return v1;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onExpr(const std::any& v1) {
  return v1;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onAdd(const std::any& v1, const std::any& v2) {
  return std::any(std::any_cast<int>(v1) + std::any_cast<int>(v2));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onSub(const std::any& v1, const std::any& v2) {
  return std::any(std::any_cast<int>(v1) - std::any_cast<int>(v2));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onTerm(const std::any& v1) {
  return v1;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onMul(const std::any& v1, const std::any& v2) {
  return std::any(std::any_cast<int>(v1) * std::any_cast<int>(v2));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onDiv(const std::any& v1, const std::any& v2) {
  return std::any(std::any_cast<int>(v1) / std::any_cast<int>(v2));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onNumber(const std::any& v1) {
  std::cerr << "onNumber:" << std::any_cast<std::string>(v1) << std::endl;
  return std::any(std::stoi(std::any_cast<std::string>(v1)));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
int main(int argc, const char** argv) {
  std::unique_ptr<Main> parser(new Main());
  std::string line;
  while(std::getline(std::cin, line)) {
    std::cout << line << std::endl;
    lilyan::Input input(line);
    auto result = parser->main(input);
    std::cout << "=> " << std::any_cast<int>(result) << std::endl;
  }
  return 0;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
