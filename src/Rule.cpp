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
  output << "Match match;" << '\n';
  output << "lilyan::Input _input(getInput());" << '\n';
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
    output << "return applyMatch(match, result);" << '\n';
  }
  output << '}' << '\n';
  if(hasRecursive()) {
    output << "void " << name_ << "(const std::any& value, std::any* result = nullptr) " << '{';
    output << "Match match;" << '\n';
    output << "lilyan::Input _input(getInput());" << '\n';
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
std::string Rule::getReturn(const std::string& value) const {
  std::ostringstream stream;
  if(hasRecursive()) {
    //stream << name_ << "(" << value << ")";
    stream << name_ << "(*match.value)";
  }
  else {
    stream << "true";
  }
  return stream.str();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Rule::hasRecursive() const {
  return !recursiveSemantics_.empty();
}
