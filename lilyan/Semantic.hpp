/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace lilyan {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Semantic {
 private:
  std::vector<std::any> values_;

 public:
  Semantic() = default;
  ~Semantic() = default;

  bool append(const std::any& value) {
    if(value.has_value()) {
      values_.push_back(value);
      return true;
    }
    return false;
  }

  const Value& operator[](size_t index) const {
    return values_.at(index - 1);
  }
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
