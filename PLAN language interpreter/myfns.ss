(define (myinterpreter list)
  (cond((null? list) list)
  (else(cons(evalExpr (car list) '()) (myinterpreter(cdr list))))))
(define (evalExpr expr id)
  (cond ((integer? expr) expr) ; return value for const
  ((symbol? expr) (lookUp id expr));look up symbol 
  ((equal? (car expr) 'prog);evaluate inner program expression
    (cond ((integer? (car(cdr expr)))(car(cdr expr)))
    (else (evalExpr (car(cdr expr)) id))))
    ((equal? (car expr) 'myignore) 0);0 for myignore
    ((equal? (car expr) 'myadd);myadd
      (+(evalExpr (car(cdr expr)) id) 
      (evalExpr (car(cdr(cdr expr))) id)))
    ((equal? (car expr) 'mymul);mymul
      (*(evalExpr (car(cdr expr)) id) 
        (evalExpr (car(cdr(cdr expr)))id)))
    ((equal? (car expr) 'myneg);myneg
      (* -1(evalExpr (car(cdr expr))id)))
    ((equal? (car expr) 'mylet);mylet
      (evalExpr (car(cdr(cdr(cdr expr))))(cons (cons (car(cdr expr))(evalExpr (car(cdr(cdr expr)))id)) id)))))
(define (lookUp id symbol);look up symbol
  (cond ((null? id) '())
    ((equal? symbol (car(car id)))(cdr(car id)))
    (else(lookUp (cdr id) symbol))))