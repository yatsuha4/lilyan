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
  : className_("Parser")
{
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void Parser::parse(const std::string& file) {
  if(getInput().read(file)) {
    std::any result;
    if(rules(&result)) {
      //dump(std::cout, result);
      result = eval(result);
      auto rules = std::any_cast<std::shared_ptr<Rules>>(result);
      putCpp(*rules);
    }
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
std::any Parser::onRule(const std::any& _name, const std::any& _semantics) {
  auto name = std::any_cast<std::smatch>(_name)[0];
  auto semantics = std::any_cast<std::shared_ptr<Semantics>>(_semantics);
  auto rule = std::make_shared<Rule>(name, *semantics);
  std::cout << rule->toString();
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
std::any Parser::tokenRule(const std::any& _match) {
  auto match = std::any_cast<std::smatch>(_match);
  auto name = match[1];
  auto repeat =
    (match[2] == "?") ? lilyan::Repeat::ZeroOne
    : (match[2] == "*") ? lilyan::Repeat::ZeroAny
    : (match[2] == "+") ? lilyan::Repeat::OneAny
    : lilyan::Repeat::One;
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::Rule>(name, repeat));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenString(const std::any& _string) {
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::String>(std::any_cast<std::string>(_string)));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::tokenRegexp(const std::any& _regexp) {
  return std::static_pointer_cast<Token>
    (std::make_shared<Token::Regexp>(std::any_cast<std::string>(_regexp)));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onActionRule(const std::any& _name, const std::any& _args) {
  auto action = std::make_shared<Action>(std::any_cast<std::smatch>(_name)[0], 
                                         std::any_cast<std::vector<int>>(_args));
  if(std::find_if(actions_.begin(), actions_.end(), 
                  [&](const std::shared_ptr<Action>& iter) {
                    return iter->getName() == action->getName();
                  }) == actions_.end()) {
    actions_.push_back(action);
  }
  return action;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onActionArg(const std::any& _arg) {
  return std::make_shared<Action>(std::any_cast<std::vector<int>>(_arg));
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArgs(const std::any& _arg) {
  std::vector<int> list;
  list.push_back(std::any_cast<int>(_arg));
  return list;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::appendArgs(const std::any& _args, const std::any& _arg) {
  auto list = std::any_cast<std::vector<int>>(_args);
  list.push_back(std::any_cast<int>(_arg));
  return list;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
std::any Parser::onArg(const std::any& value) {
  auto match = std::any_cast<std::smatch>(value);
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
  for(auto& action : actions_) {
    output_ << "virtual std::any " << action->getName() << "(";
    auto& args = action->getArgs();
    for(auto iter = args.begin(); iter != args.end(); iter++) {
      if(iter != args.begin()) {
        output_ << ", ";
      }
      output_ << "const std::any&";
    }
    output_ << ") = 0;" << '\n';
  }
  output_ << '}' << ";" << '\n';
}
/***********************************************************************//**
	$Id$
***************************************************************************/
