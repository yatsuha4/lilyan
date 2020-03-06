/***********************************************************************//**
	@file
***************************************************************************/
#include "Parser.hpp"
#include "Rule.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
Rule::Rule(const std::string& name, const Semantics& semantics)
  : name_(name)
{
  for(auto& semantic : semantics) {
    if(semantic->isRecursive(name)) {
      recursiveSemantics_.push_back(semantic);
    }
    else {
      semantics_.push_back(semantic);
    }
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Rule::toString() const {
  std::ostringstream stream;
  stream << name_ << ":" << std::endl;
  for(auto& semantic : semantics_) {
    stream << "  " << semantic->toString() << std::endl;
  }
  for(auto& semantic : recursiveSemantics_) {
    stream << "  " << semantic->toString() << std::endl;
  }
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Rule::putCpp(Parser& parser) const {
  auto& output = parser.getOutput();
  if(semantics_.empty()) {
    std::ostringstream stream;
    stream << "nothing semantic for " << name_;
    throw lilyan::Error(stream.str());
  }
  output << "bool " << name_ << "(std::any* result = nullptr) " << '{';
  output << "lilyan::Input input(getInput());" << '\n';
  for(auto& semantic : semantics_) {
    semantic->putCpp(parser, *this);
  }
  if(hasRecursive()) {
    output << "if(applyMatch(match, result)) " << '{'
           << name_ << "(*match.value, result);" << '\n'
           << "return true;" << '\n'
           << '}' << '\n'
           << "return false;" << '\n';
  }
  else {
    output << "return false;" << '\n';
  }
  output << '}' << '\n';
  if(hasRecursive()) {
    output << "void " << name_ << "(const std::any& value, std::any* result = nullptr) " << '{';
    output << "Match match;" << '\n';
    output << "lilyan::Input input(getInput());" << '\n';
    for(auto& semantic : recursiveSemantics_) {
      semantic->putCpp(parser, *this);
    }
    if(hasRecursive()) {
      output << "if(applyMatch(match, result)) " << '{'
             << name_ << "(*match.value, result);" << '\n'
             << '}' << '\n';
    }
    else {
      output << "applyMatch(match, result);" << '\n';
    }
    output << '}' << '\n';
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Rule::onMatch(Parser& parser, const std::string& value) const {
  auto& output = parser.getOutput();
  if(hasRecursive()) {
    output << "return " << name_ << "(" << value << ", result);";
  }
  else {
    output << "if(result) " << '{'
           << "*result = " << value << ";" << '\n'
           << '}' << '\n'
           << "return true;" << '\n';
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Rule::hasRecursive() const {
  return !recursiveSemantics_.empty();
}
