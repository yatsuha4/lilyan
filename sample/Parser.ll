main:
  expr -> onMainExpr($1)
  ;

expr:
  number '+' number -> onAdd($1, $3)
  number '-' number -> onSub($1, $3)
  number -> onExpr($1)
  ;

term:
  term '*' number -> onMul($1, $3)
  term '/' number -> onDiv($1, $3)
  number -> onTerm($1)
  ;

number:
  /\d+/ -> onNumber($1)
  ;
