/***********************************************************************//**
	@file
***************************************************************************/
#include "Parser.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
int main(int argc, const char** argv) {
  Parser parser;
  optionparser::OptionParser option;
  try {
    option.
      append('c', "class", "NAME", "クラス名を指定する", 
             [&](const char* arg) {
               parser.setClassName(arg);
             }).
      append('o', "output", "FILE", "出力ファイルを指定する", 
             [&](const char* arg) {
               if(!parser.getOutput().open(arg)) {
                 std::cerr << "can't open " << arg << std::endl;
                 exit(-1);
               }
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
