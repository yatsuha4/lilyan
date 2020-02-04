/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace lilyan {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Buffer {
 private:
  const std::string& buffer_;
  size_t pos_;

 public:
  Buffer(const std::string& buffer)
    : buffer_(buffer), 
      pos_(0)
  {}
  Buffer(const Buffer& src) = default;
  ~Buffer() = default;

  std::any match(const std::regex& patterm) const {
    std::smatch m;
    if(std::regex_match(buffer_.cbegin() + pos_, buffer_.cend(), m)) {
      pos_ += m[0].second - m[0].first;
      return std::any(std::string(m[1].first, m[1].second));
    }
    return std::any();
  }
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
