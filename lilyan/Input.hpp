/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace lilyan {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Input {
 private:
  std::shared_ptr<const std::string> name_;
  std::shared_ptr<const std::string> text_;
  size_t pos_;
  size_t x_;
  size_t y_;

 public:
  Input()
    : pos_(0), 
      x_(0), 
      y_(0)
  {}
  Input(const Input& src) = default;
  ~Input() = default;

  //Input& operator=(const Input& src) = default;

  bool read(const std::string& name) {
    std::ifstream stream(name);
    if(!stream.fail()) {
      set(name, 
          std::make_shared<std::string>
          (std::istreambuf_iterator<char>(stream), 
           std::istreambuf_iterator<char>()));
      return true;
    }
    return false;
  }

  void set(const std::string& name, 
           const std::shared_ptr<const std::string>& text) {
    name_ = std::make_shared<std::string>(name);
    text_ = text;
    pos_ = 0;
    x_ = 0;
    y_ = 0;
  }

  char fetch(size_t offset = 0) const {
    return (pos_ + offset < text_->size()) ? text_->at(pos_ + offset) : 0;
  }

  std::any match(const std::string& string) {
    if(std::equal(string.begin(), string.end(), text_->begin() + pos_)) {
      seek(string.length());
      return std::any(string);
    }
    return std::any();
  }

  std::any match(const std::regex& pattern) {
    std::smatch m;
    if(std::regex_search(text_->begin() + pos_, text_->end(), 
                         m, pattern, 
                         std::regex_constants::match_continuous)) {
      seek(m[0].second - m[0].first);
      //return std::any(std::string(m[0].first, m[0].second));
      return std::any(m);
    }
    return std::any();
  }

  std::any getString(const std::string& lq, 
                     const std::string& rq, 
                     const std::string& escape = "") {
    if(std::equal(lq.begin(), lq.end(), text_->begin() + pos_)) {
      std::string string;
      for(size_t i = lq.size();; i++) {
        if(std::equal(rq.begin(), rq.end(), text_->begin() + pos_ + i)) {
          seek(i + rq.size());
          return std::any(string);
        }
        auto c = fetch(i);
        if(c == '\0') {
          throw Error("string is not terminate");
        }
        else if(escape.find(c) != std::string::npos) {
          string.push_back(fetch(++i));
        }
        else {
          string.push_back(c);
        }
      }
    }
    return std::any();
  }

  void seek(size_t offset) {
    assert(pos_ + offset <= text_->size());
    for(size_t i = 0; i < offset; i++) {
      if(fetch(i) == '\n') {
        x_ = 0;
        y_++;
      }
      else {
        x_++;
      }
    }
    pos_ += offset;
  }

  bool isEnd() const {
    return pos_ >= text_->size();
  }

  std::string toString() const {
    std::ostringstream stream;
    stream << y_ << ":" << x_ << " '" << text_->substr(pos_, 20) << "'";
    return stream.str();
  }
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
