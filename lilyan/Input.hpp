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
  const std::string& text_;
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

  std::any match(const std::regex& patterm) const {
    std::smatch m;
    if(std::regex_match(text_.cbegin() + pos_, text_.cend(), m)) {
      seek(pos_ + m[0].second - m[0].first);
      return std::any(std::string(m[1].first, m[1].second));
    }
    return std::any();
  }

  void seek(size_t pos) {
    assert(pos >= pos_ && pos <= text_.size());
    for(auto i = pos_; i < pos; i++) {
      if(text_[i] == '\d') {
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
    return pos_ >= text_.size();
  }

  std::string toString() const {
    std::sstream stream;
    stream << y_ << ":" << x_;
    return stream.str();
  }
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
