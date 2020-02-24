/***********************************************************************//**
	@file
***************************************************************************/
#include "Parser.hpp"
#include "Rule.hpp"
#include "Semantic.hpp"
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
Semantic::Semantic(const std::shared_ptr<Tokens>& tokens, 
                   const std::shared_ptr<Action>& action)
  : tokens_(tokens), 
    action_(action)
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Semantic::isRecursive(const std::string& name) const {
  return tokens_->isRecursive(name);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Semantic::putCpp(Parser& parser, const Rule& rule) const {
  auto& output = parser.getOutput();
  output << '{';
  output << "lilyan::Input _input(getInput());" << '\n';
  output << action_->prematch() << '\n';
  output << "if(";
  for(size_t i = 0, n = tokens_->size(); i < n; i++) {
    if(i > 0) {
      output << " &&" << '\n' << "   ";
    }
    output << action_->match(i, rule, *tokens_->at(i));
  }
  output << ") " << '{';
  output << "setMatch(match, " << action_->postmatch(parser) << ");" << '\n';
  output << '}' << '\n';
  output << "getInput() = _input;" << '\n';
  output << '}' << '\n';
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::string Semantic::toString() const {
  std::ostringstream stream;
  stream << tokens_->toString() << " -> " << action_->toString();
  return stream.str();
}
