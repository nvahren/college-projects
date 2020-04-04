;; scheme daily homework 7
;; name: Nathan Vahrenberg
;; date: 5 February 2016

(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp16/scheme_dailies/d7/paradigms_d7.scm")
(use-modules (ice-9 paradigms_d7))

;; greatest
;; return the greatest value in a tup, e.g., (1 3 2) -> 3
(define (greatest tup)
	(if (null? (cdr tup)) (car tup)
		(if (> (car tup) (greatest (cdr tup)))
			(car tup)
			(greatest (cdr tup))
		)
	)
)

;; positionof
;; you may assume that the given tup actually contains n
;; e.g., (positionof 23 (1 52 23 9)) -> 3
(define (positionof n tup)
	(if (eqv? n (car tup)) ;; if the car of tup is our desired value
		1 ;; start counting, stop recursing
		(+ 1 (positionof n (cdr tup))) ;; otherwise, keep recursing
	)
)

;; value
;; given a game state, return the value of that state:
;; 10 if it's a win
;; -10 if it's a loss
;; 0 if it is either a draw or not an ending state

(define (value p gs)
	(if (win? p gs) ;; if p wins
		10 ;; return 10
		(if (win? (other p) gs) ;; if other p wins
			-10 ;; return -10
			0 ;; game is undecided, return 0
		)
	)
)

;; tests for greatest
(display (greatest '(1 9 2)))
(display "\n")

(display (greatest '(143 8 31324 24)))
(display "\n")

;; tests for positionof
(display (positionof 23 '(1 52 23 9)))
(display "\n")

(display (positionof 50 '(50 45 1 52 23 9 102)))
(display "\n")

;; tests for value
(display (value 'x '(x o e o x e e e x)))
(display "\n")

(display (value 'x '(o o o x x e e e e)))
(display "\n")

(display (value 'x '(o o e x x e e e e)))
(display "\n")

;; correct output:
;;   $ guile d6.scm
;;   9
;;   31324
;;   3
;;   1
;;   10
;;   -10
;;   0

