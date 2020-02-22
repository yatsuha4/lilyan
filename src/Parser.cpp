/***********************************************************************//**
	@file
***************************************************************************/
#include "Action.hpp"
#include "Parser.hpp"
#include "Rule.hpp"
/***********************************************************************//**
	@brief 
***************************************************************************/
void Parser::parse(const std::string& file) {
  if(getInput().read(file)) {
    auto result = rules();
    dump(std::cout, result);
    eval(result);
  }
  else {
    std::ostringstream stream;
    stream << "read error, '" << file << "'";
    error(stream.str());
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onGetToken(const std::string& pattern) {
  if(pattern == "''") {
    return getInput().getString("'", "'");
  }
  else if(pattern == "\"\"") {
    return getInput().getString("\"", "\"");
  }
  else if(pattern == "//") {
    return getInput().getString("/", "/");
  }
  return super::onGetToken(pattern);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onRules(const lilyan::List& args) {
  auto rules = std::make_shared<Rules>();
  auto rule = std::any_cast<std::shared_ptr<Rule>>(args[1]);
  rules->push_back(rule);
  return std::any(rules);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::appendRules(const lilyan::List& args) {
  auto rules = std::any_cast<std::shared_ptr<Rules>>(args[1]);
  auto rule = std::any_cast<std::shared_ptr<Rule>>(args[2]);
  rules->push_back(rule);
  return std::any(rules);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onRule(const lilyan::List& args) {
  auto name = std::any_cast<std::smatch>(args[1])[0];
  auto semantics = std::any_cast<std::shared_ptr<Semantics>>(args[2]);
  auto rule = std::make_shared<Rule>(name, semantics);
  std::cout << rule->toString();
  return rule;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onSemantics(const lilyan::List& args) {
  auto semantics = std::make_shared<Semantics>();
  semantics->push_back(std::any_cast<std::shared_ptr<Semantic>>(args[1]));
  return semantics;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::appendSemantics(const lilyan::List& args) {
  auto semantics = std::any_cast<std::shared_ptr<Semantics>>(args[1]);
  auto semantic = std::any_cast<std::shared_ptr<Semantic>>(args[2]);
  semantics->push_back(semantic);
  return semantics;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onSemantic(const lilyan::List& args) {
  auto tokens = std::any_cast<std::shared_ptr<Tokens>>(args[1]);
  auto action = std::any_cast<std::shared_ptr<Action>>(args[2]);
  auto semantic = std::make_shared<Semantic>(tokens, action);
  return semantic;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onTokens(const lilyan::List& args) {
  auto tokens = std::make_shared<Tokens>();
  auto token = std::any_cast<std::shared_ptr<Token>>(args[1]);
  tokens->push_back(token);
  return tokens;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::appendTokens(const lilyan::List& args) {
  auto tokens = std::any_cast<std::shared_ptr<Tokens>>(args[1]);
  auto token = std::any_cast<std::shared_ptr<Token>>(args[2]);
  tokens->push_back(token);
  return tokens;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenRule(const lilyan::List& args) {
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::Rule>(std::any_cast<std::smatch>(args[1])[0]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenString(const lilyan::List& args) {
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::String>(std::any_cast<std::string>(args[1])));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenRegexp(const lilyan::List& args) {
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::Regexp>(std::any_cast<std::string>(args[1])));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onActionRule(const lilyan::List& args) {
  return std::make_shared<Action>(std::any_cast<std::smatch>(args[1])[0], 
                                  std::any_cast<std::vector<int>>(args[2]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onActionArg(const lilyan::List& args) {
  return std::make_shared<Action>(std::any_cast<std::vector<int>>(args[1]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArgs(const lilyan::List& args) {
  std::vector<int> list;
  list.push_back(std::any_cast<int>(args[1]));
  return std::any(list);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::appendArgs(const lilyan::List& args) {
  auto list = std::any_cast<std::vector<int>>(args[1]);
  list.push_back(std::any_cast<int>(args[2]));
  return std::any(list);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArg(const lilyan::List& args) {
  auto match = std::any_cast<std::smatch>(args[1]);
  return std::any(std::stoi(match[1]));
}
/***********************************************************************//**
	$Id$
***************************************************************************/
