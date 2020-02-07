main:
  expr -> onMainExpr($1)
  ;

expr:
  number -> onExpr($1)
  expr '+' number -> onAdd($1, $3)
  expr '-' number -> onSub($1, $3)
  ;

term:
  term '*' number -> onMul($1, $3)
  term '/' number -> onDiv($1, $3)
  number -> onTerm($1)
  ;

number:
  /\d+/ -> onNumber($1)
  ;
