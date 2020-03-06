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
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace lilyan {
using List = std::vector<std::any>;

enum class Repeat {
  One, 
  OneAny, 
  ZeroAny, 
  ZeroOne
};
}

#include "lilyan/Parser.hpp"
/***********************************************************************//**
	$Id$
***************************************************************************/
