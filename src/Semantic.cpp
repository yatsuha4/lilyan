/***********************************************************************//**
	@file
***************************************************************************/
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
std::string Semantic::toString() const {
  std::ostringstream stream;
  stream << tokens_->toString() << " -> " << action_->toString();
  return stream.str();
}
