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
  std::reference_wrapper<const std::string> text_;
  size_t pos_;
  size_t x_;
  size_t y_;

 public:
  Input(const std::string& text)
    : text_(text), 
      pos_(0), 
      x_(0), 
      y_(0)
  {}
  Input(const Input& src) = default;
  ~Input() = default;

  //Input& operator=(const Input& src) = default;

  std::any match(const std::string& string) {
    if(std::equal(std::begin(string), std::end(string), std::begin(text_.get()))) {
      seek(pos_ + string.length());
      return std::any(string);
    }
    return std::any();
  }

  std::any match(const std::regex& pattern) {
    std::cerr << text_.get().substr(pos_) << std::endl;
    std::smatch m;
    if(std::regex_search(text_.get().cbegin() + pos_, text_.get().cend(), 
                         m, pattern, 
                         std::regex_constants::match_continuous)) {
      std::cerr << "match" << std::endl;
      seek(pos_ + m[0].second - m[0].first);
      return std::any(std::string(m[0].first, m[0].second));
    }
    return std::any();
  }

  std::any matchRegex(const std::string& pattern) {
    std::cerr << "/" << pattern << "/" << std::endl;
    return match(std::regex(pattern));
  }


  void seek(size_t pos) {
    assert(pos >= pos_ && pos <= text_.get().size());
    for(auto i = pos_; i < pos; i++) {
      if(text_.get()[i] == '\n') {
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
    return pos_ >= text_.get().size();
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
