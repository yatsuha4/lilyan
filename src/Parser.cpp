/***********************************************************************//**
	@file
***************************************************************************/
#include "Action.hpp"
#include "Parser.hpp"
#include "Rule.hpp"
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
Parser::Parser()
  : className_("Parser"), 
    rulePrefix_("rule_")
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Parser::parse(const std::filesystem::path& path) {
  if(pushInput(path)) {
    std::any result;
    if(rule_rules(&result)) {
      //dump(std::cout, result);
      result = eval(result);
      auto rules = std::any_cast<std::shared_ptr<Rules>>(result);
      putCpp(*rules);
    }
    else {
      error("syntax error");
    }
  }
  else {
    std::ostringstream stream;
    stream << "read error, '" << path << "'";
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
std::any Parser::onRules(const std::any& _rules) {
  auto rules = std::make_shared<Rules>();
  for(auto& _rule : std::any_cast<std::vector<std::any>>(_rules)) {
    auto rule = std::any_cast<std::shared_ptr<Rule>>(_rule);
    rules->push_back(rule);
  }
  return rules;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onRule(const std::smatch& _name, const std::any& _semantics) {
  auto name = rulePrefix_ + _name[0].str();
  auto semantics = std::any_cast<std::shared_ptr<Semantics>>(_semantics);
  auto rule = std::make_shared<Rule>(name, *semantics);
  //std::cout << rule->toString();
  return rule;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onSemantics(const std::any& _semantics) {
  auto semantics = std::make_shared<Semantics>();
  for(auto& _semantic : std::any_cast<std::vector<std::any>>(_semantics)) {
    auto semantic = std::any_cast<std::shared_ptr<Semantic>>(_semantic);
    semantics->push_back(semantic);
  }
  return semantics;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onSemantic(const std::any& _tokens, const std::any& _action) {
  auto tokens = std::any_cast<std::shared_ptr<Tokens>>(_tokens);
  auto action = std::any_cast<std::shared_ptr<Action>>(_action);
  auto semantic = std::make_shared<Semantic>(tokens, action);
  return semantic;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onTokens(const std::any& _tokens) {
  auto tokens = std::make_shared<Tokens>();
  for(auto& _token : std::any_cast<std::vector<std::any>>(_tokens)) {
    auto token = std::any_cast<std::shared_ptr<Token>>(_token);
    tokens->push_back(token);
  }
  return tokens;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenEof() {
  return std::static_pointer_cast<Token>(std::make_shared<Token::Eof>());
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenRule(const std::smatch& _name, 
                           const std::any& _repeat) {
  auto repeat = _repeat.has_value()
    ? std::any_cast<lilyan::Repeat>(_repeat)
    : lilyan::Repeat::One;
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::Rule>(rulePrefix_ + _name[0].str(), repeat));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenString(const std::string& string) {
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::String>(string));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenRegexp(const std::string& regexp) {
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::Regexp>(regexp));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onActionRule(const std::smatch& _name, 
                              const std::any& _args) {
  auto args = _args.has_value()
    ? std::any_cast<std::vector<int>>(_args)
    : std::vector<int>();
  auto action = std::make_shared<Action::Func>(_name[0].str(), args);
  actionFuncs_.push_back(action);
  return std::static_pointer_cast<Action>(action);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onActionConst(const std::smatch& match) {
  return std::static_pointer_cast<Action>
    (std::make_shared<Action::Const>(match[0]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onActionArg(const std::any& _arg) {
  return std::static_pointer_cast<Action>
    (std::make_shared<Action::Arg>(std::any_cast<int>(_arg)));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArgs(const std::any& _arg, const std::any& _args_r) {
  std::vector<int> list;
  list.push_back(std::any_cast<int>(_arg));
  for(auto& iter : std::any_cast<std::vector<std::any>>(_args_r)) {
    list.push_back(std::any_cast<int>(iter));
  }
  return list;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArg(const std::smatch& match) {
  return std::any(std::stoi(match[1]));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Parser::putCpp(const Rules& rules) {
  output_ << "#include \"lilyan/lilyan.hpp\"" << '\n';
  output_ << "class " << className_ << " : public lilyan::Parser " << '{';
  output_ << '-' << "public:" << '\n';
  for(auto& rule : rules) {
    rule->putCpp(*this);
  }
  output_ << '-' << "protected:" << '\n';
  output_ << className_ << "() = default;" << '\n';
  output_ << "~" << className_ << "() override = default;" << '\n';
  for(auto func = actionFuncs_.begin(); func != actionFuncs_.end(); func++) {
    if(std::find_if(actionFuncs_.begin(), func, 
                    [&](const auto& iter) {
                      return iter->getName() == (*func)->getName() && 
                        iter->getTypes() == (*func)->getTypes();
                    }) == func) {
      (*func)->declare(output_);
    }
  }
  output_ << '}' << ";" << '\n';
}
/***********************************************************************//**
	$Id$
***************************************************************************/
