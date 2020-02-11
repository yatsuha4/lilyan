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

  std::any onAdd(const List& args) override;
  std::any onSub(const List& args) override;
  std::any onMul(const List& args) override;
  std::any onDiv(const List& args) override;
  std::any onNumber(const List& args) override;
};
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onAdd(const List& args) {
  return std::any(std::any_cast<int>(args[1]) + std::any_cast<int>(args[2]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onSub(const List& args) {
  return std::any(std::any_cast<int>(args[1]) - std::any_cast<int>(args[2]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onMul(const List& args) {
  return std::any(std::any_cast<int>(args[1]) * std::any_cast<int>(args[2]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onDiv(const List& args) {
  return std::any(std::any_cast<int>(args[1]) / std::any_cast<int>(args[2]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Main::onNumber(const List& args) {
  //std::cerr << "onNumber:" << std::any_cast<std::string>(args[1]) << std::endl;
  return std::any(std::stoi(std::any_cast<std::string>(args[1])));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
int main(int argc, const char** argv) {
  std::unique_ptr<Main> parser(new Main());
  std::string line;
  while(std::getline(std::cin, line)) {
    std::cout << ">" << line << std::endl;
    lilyan::Input input(line);
    auto ast = parser->main(input);
    parser->dump(std::cerr, ast);
    auto result = parser->eval(ast);
    std::cout << "=> " << std::any_cast<int>(result) << std::endl;
  }
  return 0;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
