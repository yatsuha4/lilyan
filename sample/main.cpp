/***********************************************************************//**
	@file
***************************************************************************/
#include "Parser.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
int main(int argc, const char** argv) {
  Parser parser;
  std::string line;
  while(std::getline(std::cin, line)) {
    std::cout << ">" << line << std::endl;
    std::any result = parser.parse(line);
    std::cout << "=>";
    for(auto& value : std::any_cast<std::vector<std::any>>(result)) {
      std::cout << " " << std::any_cast<int>(value);
    }
    std::cout << std::endl;
  }
  return 0;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
