; this is a simple test library

;(let (x y) (1 2) (+ x y))

;((lambda (x y) (+ x y)) 3 4)

(letrec
    (fact)
    ((lambda (n) (if (eq n 0) 1 (* n (fact (- n 1))))))
    (fact 10)
)
