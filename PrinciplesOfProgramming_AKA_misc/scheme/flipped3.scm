(define (union listA listB) 
  
  (cond 
   ((in (car listA) listB) (cons (car listA) (union (cdr listA) listB)))
   (else (union (cdr listA) listB))
   )

)

(define (main)

  (display (union '(1 2 3 A D) '(A 4 5 6 D)))
)

(main)