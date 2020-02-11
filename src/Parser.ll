syntax:
  rule		-> $1
  syntax rule	-> appendRule($2)
  ;

rule:
  name ':' expr ';' -> null
  ;

expr:
  cond		->
  expr '|' cond	-> 
  ;

cond:
  list '->' func	->
  '->' func		->
  ;

list
  : term
  | list term
  ;

term
  : /\w+/		-> termRule($1)
  | "'" /.*/ "'"	-> termString($2)
  | '"' /.*/ '"'	-> termString($2)
  | /(?<!\\)\/.*?(?<!\\)\//	-> termRegexp($1)
  ;

func
  : /\w+/ '(' args ')'	-> func($1, $3)
  | arg			-> func($1)
  |			-> funcNull()
  ;

args
  : arg			-> onArgs($1)
  | args ',' arg	-> appendArgs($1, $3)
  ;

arg
  : /\$\d+/		-> onArg($1)
  ;

comment
  : '//' /.*?$/		->
  | '/*' /.*?/ '*/'	->
  ;
