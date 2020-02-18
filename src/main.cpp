/***********************************************************************//**
	@file
***************************************************************************/
#include <iostream>

#include "lilyan/lilyan.hpp"
#include "optionparser/OptionParser.hpp"

#include "Parser.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
int main(int argc, const char** argv) {
  optionparser::OptionParser option;
  std::string output;
  try {
    option.
      append('o', "output", "FILE", "出力ファイルを指定する", 
             [&](const char* arg) {
               output.assign(arg);
             }).
      append('h', "help", nullptr, "このメッセージを表示する", 
             [&](const char*) {
               std::cerr << option.help();
               exit(-1);
             }).
      parse(argc, argv);
  }
  catch(const optionparser::OptionParser::Error& e) {
    std::cerr << e.message << std::endl;
    exit(-1);
  }
  Parser parser;
  try {
    for(const char* file : option) {
      parser.parse(file);
    }
  }
  catch(const lilyan::Error& e) {
    std::cerr << e.getMessage() << std::endl;
    exit(-1);
  }
  return 0;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
