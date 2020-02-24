/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include <iostream>
#include <map>

#include "lilyan/lilyan.hpp"
#include "optionparser/OptionParser.hpp"

enum class Repeat {
  Null, 
  ZeroOne, 
  ZeroAny, 
  OneAny
};

class Action;
class Output;
class Parser;
class Rule;
class Rules;
class Semantic;
class Semantics;
class Token;
class Tokens;
