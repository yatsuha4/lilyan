rules:
  rule* -> onRules($1)
  ;

rule:
  /\w+/ ':' semantics ';' -> onRule($1, $3)
  ;

semantics:
  semantic+ -> onSemantics($1)
  ;

semantic:
  tokens '->' action -> onSemantic($1, $3)
  ;

tokens:
  token+ -> onTokens($1)
  ;

token:
  "<<EOF>>" -> tokenEof()
  /\w+/ token_r? -> tokenRule($1, $2)
  "''" -> tokenString($1)
  '""' -> tokenString($1)
  '//' -> tokenRegexp($1)
  ;

token_r:
  '?' -> <lilyan::Repeat::ZeroOne>
  '*' -> <lilyan::Repeat::ZeroAny>
  '+' -> <lilyan::Repeat::OneAny>
  ;

action:
  /\w+/ '(' args? ')' -> onActionRule($1, $3)
  '<' /[\w:]+/ '>' -> onActionConst($2)
  arg -> onActionArg($1)
  ;

args:
  arg args_r* -> onArgs($1, $2)
  ;

args_r:
  ',' arg -> $2
  ;

arg:
  /\$(\d+)/ -> onArg($1)
  ;
