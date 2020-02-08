main:
  expr -> onMainExpr($1)
  ;

expr:
  expr '+' term -> onAdd($1, $3)
  expr '-' term -> onSub($1, $3)
  term -> onExpr($1)
  ;

term:
  term '*' number -> onMul($1, $3)
  term '/' number -> onDiv($1, $3)
  number -> onTerm($1)
  ;

number:
  /\d+/ -> onNumber($1)
  '(' expr ')' -> toValue($2)
  ;
