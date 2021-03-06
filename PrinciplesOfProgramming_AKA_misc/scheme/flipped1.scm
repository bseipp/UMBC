==define (triple-everything x)
  (cond 
   ((null? x) x)
   (else (cons (* (car x) 3) (triple-everything (cdr x)))))
)

(define (main ) 
(display (triple-everything '(8 33.5 12/5 15-6i)))
(printf "\n")
(display (triple-everything '(100 357 1 7)))
(printf "\n")
)

(main)