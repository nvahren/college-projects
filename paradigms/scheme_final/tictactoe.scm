;; scheme tictactoe homework
;; name: Nathan Vahrenberg
;; date: 10 February 2016

(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp16/scheme_tictactoe/paradigms_ttt.scm")
(use-modules (ice-9 paradigms_ttt))

(define (greatest tup)
	(if (null? (cdr tup)) (car tup)
		(if (> (car tup) (greatest (cdr tup)))
			(car tup)
			(greatest (cdr tup))
		)
	)
)

(define (positionof n tup)
	(if (eqv? n (car tup)) ;; if the car of tup is our desired value
		1 ;; start counting, stop recursing
		(+ 1 (positionof n (cdr tup))) ;; otherwise, keep recursing
	)
)

(define (value p gs)
	(if (win? p gs) ;; if p wins
		10 ;; return 10
		(if (win? (other p) gs) ;; if other p wins
			-10 ;; return -10
			0 ;; game is undecided, return 0
		)
	)
)

(define (sum* ttup p)
	(if (null? ttup) 0 ;; if null return 0
		(if (not (pair? (car (car ttup))))
			(+ (value p (car ttup)) (sum* (cdr ttup) p))
			(+ (sum* (car ttup) p) (sum* (cdr ttup) p))
		)
	)
)

;; MODIFY this function so that given the game tree 
;; (where the current situation is at the root),
;; it returns the recommendation for the next move
(define (nextmove p gt)
    (if (> (sum* (car (cdr gt)) p) (sum* (cdr (cdr gt)) p)) ;; if "left" > "right"
    	(car (car (cdr gt))) ;; return the first move on left
    	(car (cdr (cdr gt))) ;; return the first move on right
    )
)

;; onegametree is defined in paradigms_ttt
;; be sure to look at that file!

;; what is the current game situation?
(display "Current State:     ")
(display (car (onegametree)))
(display "\n")

;; test of nextmove, where should we go next?
(display "Recommended Move:  ")
(display (nextmove 'x (onegametree)))
(display "\n")

;; correct output:
;;   $ guile tictactoe.scm
;;   Current State:     (x o x o o e e x e)
;;   Recommended Move:  (x o x o o x e x e)

