; File: Average.scm

(define a 0)
(define b 0)
(define c 0)
(display "Enter a value\n")
(set! a (read))
(display "Enter a value\n")
(set! b (read))
(display "Enter a value\n")
(set! c (read))
(define avg 0)
(set! avg (/ (+ a b c) 3))
(printf "The average is ~s.\n" avg)