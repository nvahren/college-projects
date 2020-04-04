;; scheme daily homework 4
;; name: Nathan Vahrenberg
;; date: 01/29/16

(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp16/scheme_dailies/d4/paradigms_d4.scm")
(use-modules (ice-9 paradigms_d4))

;; filterN
(define (filterN n m lat)
	(if (null? lat) '() ;; if there's no more list, stop recursing
		(if (number? (car lat)) ;; if the first element is a number
			(if (> (add1 (car lat)) n) ;; and greater than or equal to n
				(if (< (sub1 (car lat)) m) ;; and less than or equal to m
					(cons (car lat) (filterN n m (cdr lat))) ;; add it to the return list, and recurse
					(filterN n m (cdr lat)) ;; recurse without adding to list
				)
				(filterN n m (cdr lat)) ;; recurse without adding to list
			)
			(filterN n m (cdr lat)) ;; recurse without adding to list
		)
	)
)
    ;; currently this function just returns the lat as it is given
    ;; change the function so that it returns /only/ the numbers
    ;; >= n and <= m
    ;; see below for examples...

;; tests!
(display (filterN 4 6 '(1 turkey 5 9 4 bacon 6 cheese)))
(display "\n")

(display (filterN 4 6 '(4 4 4 1 1 bacon 9 9 9 6 6 6 1 4 5)))
(display "\n")

;; correct output:
;;   $ guile d4.scm
;;   (5 4 6)
;;   (4 4 4 6 6 6 4 5)

