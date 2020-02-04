main:
  expr -> onMainExpr($1)
  ;

expr:
  term -> onExpr($1)
  expr '+' term -> onAdd($1, $3)
  expr '-' term -> onSub($1, $3)
  ;

term:
  number -> onTerm($1)
  term '*' number -> onMul($1, $3)
  term '/' number -> onDiv($1, $3)
  ;

number:
  /[0-9]+/ -> onNumber($1)
  ;
