/***********************************************************************//**
	@file
***************************************************************************/
#pragma once
/***********************************************************************//**
	@brief 
***************************************************************************/
#include <any>
#include <array>
#include <cassert>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace lilyan {
using List = std::vector<std::any>;

enum class Repeat {
  Null, 
  ZeroOne, 
  ZeroAny, 
  OneAny
};
}

#include "lilyan/Parser.hpp"
/***********************************************************************//**
	$Id$
***************************************************************************/
