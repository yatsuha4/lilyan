/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "lilyan/Action.hpp"
#include "lilyan/Error.hpp"
#include "lilyan/Input.hpp"

namespace lilyan {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Parser {
 protected:
  struct Match {
    std::optional<std::any> value;
    std::shared_ptr<Input> input;
  };

 private:
  std::shared_ptr<Input> input_;
  std::shared_ptr<Input> arrival_;
  std::map<std::string, std::shared_ptr<const std::string>> cache_;

 public:
  bool pushInput(const std::filesystem::path& path) {
    auto name = path.native();
    if(auto iter = cache_.find(name); iter != cache_.end()) {
      pushInput(iter->second, std::make_shared<std::string>(name));
    }
    else {
      std::ifstream stream(path);
      if(!stream.fail()) {
        auto text = std::make_shared<std::string>
          (std::istreambuf_iterator<char>(stream), 
           std::istreambuf_iterator<char>());
        cache_.insert(std::make_pair(name, text));
        pushInput(text, std::make_shared<std::string>(name));
      }
      else {
        return false;
      }
    }
    return true;
  }

  void pushInput(const std::shared_ptr<const std::string>& text, 
                 const std::shared_ptr<const std::string>& name = nullptr) {
    input_ = std::make_shared<Input>(input_, text, name);
  }

  void popInput() {
    assert(input_);
    if(auto parent = input_->getParent()) {
      input_ = std::make_shared<Input>(*parent);
    }
    else {
      input_.reset();
    }
  }

  std::any eval(const std::any& value) {
    if(value.type() == typeid(std::shared_ptr<Action>)) {
      auto action = std::any_cast<std::shared_ptr<Action>>(value);
      return action->func();
    }
    else if(value.type() == typeid(std::vector<std::any>)) {
      std::vector<std::any> list;
      for(auto& iter : std::any_cast<std::vector<std::any>>(value)) {
        list.push_back(eval(iter));
      }
      return list;
    }
    return value;
  }

  void dump(std::ostream& output, 
            const std::any& value, 
            const std::string& indent = "") const {
    if(value.type() == typeid(std::shared_ptr<List>)) {
      auto& list = *std::any_cast<std::shared_ptr<List>>(value);
      for(auto iter = list.begin(); iter != list.end(); iter++) {
        if(iter == list.begin()) {
          if(!indent.empty()) {
            output << std::endl << indent;
          }
          output << "(";
        }
        else {
          output << " ";
        }
        dump(output, *iter, indent + "  ");
      }
      output << ")";
    }
    else {
      output << toString(value);
    }
    if(indent.empty()) {
      output << std::endl;
    }
  }

  virtual std::string toString(const std::any& value) const {
    if(value.type() == typeid(std::string)) {
      std::ostringstream stream;
      stream << "'" << std::any_cast<std::string>(value) << "'";
      return stream.str();
    }
    else if(value.type() == typeid(Action)) {
      return std::string(std::any_cast<Action>(value).name);
    }
    return std::string("?");
  }

  virtual void error(const std::string& message) {
    std::ostringstream stream;
    stream << message;
    if(arrival_) {
      stream << " at " << arrival_->toString();
    }
    throw Error(stream.str());
  }

  virtual void warning(const std::string& message) {
    std::cerr << "WARNING: " << message << " at " << getInput().toString() << std::endl;
  }

 protected:
  Parser() = default;
  virtual ~Parser() = default;

  Input& getInput() const {
    return *input_;
  }

  bool append(List& list, const std::any& value) {
    if(value.has_value()) {
      list.push_back(value);
      return true;
    }
    return false;
  }

  virtual bool getToken(const std::string& pattern, std::any* result = nullptr) {
    return _getToken(pattern, result);
  }

  virtual std::any onGetToken(const std::string& pattern) {
    return getInput().match(pattern);
  }

  virtual bool getToken(const std::regex& pattern, std::any* result = nullptr) {
    return _getToken(pattern, result);
  }

  virtual std::any onGetToken(const std::regex& pattern) {
    return getInput().match(pattern);
  }

  virtual bool skip() {
    for(size_t i = 0;; i++) {
      auto c = input_->fetch(i);
      if(c == '\0') {
        return false;
      }
      else if(c < '\0' || c > ' ') {
        input_->seek(i);
        break;
      }
    }
    if(!arrival_ || *arrival_ < *input_) {
      arrival_ = std::make_shared<Input>(*input_);
    }
    return true;
  }

  std::any checkValue(const std::any& value) {
    assert(value.has_value());
    return value;
  }

  void setMatch(Match& match, const std::any& value) {
    if(match.value) {
      warning("conflict rule");
    }
    else {
      match.value = value;
      match.input = std::make_shared<Input>(getInput());
    }
  }

  bool applyMatch(const Match& match, std::any* result) {
    if(match.value) {
      if(result) {
        *result = *match.value;
      }
      input_ = match.input;
      return true;
    }
    return false;
  }

  bool isMatch(Repeat repeat, 
               std::function<bool(std::any*)> func, 
               std::any* result = nullptr) {
    switch(repeat) {
    case Repeat::One:
      return func(result);
    case Repeat::OneAny:
    case Repeat::ZeroAny:
      {
        std::vector<std::any> list;
        std::any value;
        while(func(&value)) {
          list.push_back(value);
        }
        if(repeat == Repeat::ZeroAny || !list.empty()) {
          *result = list;
          return true;
        }
      }
      break;
    case Repeat::ZeroOne:
      if(!func(result)) {
        result->reset();
      }
      return true;
    }
    return false;
  }

  bool isEof() {
    return !skip();
  }

 private:
  template<class T>
  bool _getToken(const T& pattern, std::any* result) {
    if(skip()) {
      auto value = onGetToken(pattern);
      if(value.has_value()) {
        if(result) {
          *result = value;
        }
        return true;
      }
    }
    return false;
  }
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
