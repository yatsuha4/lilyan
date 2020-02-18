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

  std::any match(const std::string& string) {
    if(std::equal(string.begin(), string.end(), text_->begin() + pos_)) {
      seek(pos_ + string.length());
      return std::any(string);
    }
    return std::any();
  }

  std::any match(const std::regex& pattern) {
    std::smatch m;
    if(std::regex_search(text_->begin() + pos_, text_->end(), 
                         m, pattern, 
                         std::regex_constants::match_continuous)) {
      seek(pos_ + m[0].second - m[0].first);
      return std::any(std::string(m[0].first, m[0].second));
    }
    return std::any();
  }

  void seek(size_t pos) {
    assert(pos >= pos_ && pos <= text_->size());
    for(auto i = pos_; i < pos; i++) {
      if(text_->at(i) == '\n') {
        x_ = 0;
        y_++;
      }
      else {
        x_++;
      }
    }
    pos_ = pos;
  }

  bool isEnd() const {
    return pos_ >= text_->size();
  }

  std::string toString() const {
    std::ostringstream stream;
    stream << y_ << ":" << x_;
    return stream.str();
  }

};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
