/***********************************************************************//**
	@file
***************************************************************************/
#include "Rule.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
Rule::Rule(const std::string& name, 
           const std::shared_ptr<Semantics>& semantics)
  : name_(name), 
    semantics_(semantics)
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Rule::toString() const {
  std::ostringstream stream;
  stream << name_ << ":" << std::endl;
  for(auto& semantic : *semantics_) {
    stream << "  " << semantic->toString() << std::endl;
  }
  return stream.str();
}
