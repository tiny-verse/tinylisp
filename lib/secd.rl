; Standard library for the SECD backend version of the tinyLISP

(defun not (x)
    (if x nil t)
)

(defun and (x y)
    (if x
        (if y t nil)
        nil
    )
)

(defun or (x y)
    (if x
        t
        (if y t nil)
    )
)

; Returns true if the argument is nil, false otherwise
(defun null (x)
    (eq x nil)
)

; atom is anything that is not cons
(defun atom (x)
    (if (consp x) nil t)
)



(defun length (x)
    (if (null x)
        0
        (+ 1 (length (cdr x)))
    )
)




; silly stuff for testing

(defun fact (n)
    (if (eq n 0)
        1
        (* n (fact (-n 1)))
    )
)

(defun fib (n)
    (if (eq n 0)
        1
        (if (eq n 1)
            1
            (+ (fib (-n 1)) (fib (- n 2)))
        )
    )
)

