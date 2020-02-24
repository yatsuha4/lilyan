rules:
  rule -> onRules($1)
  rules rule -> appendRules($1, $2)
  ;

rule:
  /\w+/ ':' semantics ';' -> onRule($1, $3)
  ;

semantics:
  semantic -> onSemantics($1)
  semantics semantic -> appendSemantics($1, $2)
  ;

semantic:
  tokens '->' action -> onSemantic($1, $3)
  ;

tokens:
  token -> onTokens($1)
  tokens token -> appendTokens($1, $2)
  ;

token:
  /(\w+)([\?\*\+])?/ -> tokenRule($1)
  "''" -> tokenString($1)
  '""' -> tokenString($1)
  '//' -> tokenRegexp($1)
  ;

action:
  /\w+/ '(' args ')' -> onActionRule($1, $3)
  arg -> onActionArg($1)
  ;

args:
  arg -> onArgs($1)
  args ',' arg -> appendArgs($1, $3)
  ;

arg:
  /\$(\d+)/ -> onArg($1)
  ;
