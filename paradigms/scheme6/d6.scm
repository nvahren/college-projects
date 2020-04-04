;; scheme daily homework 6
;; name: Nathan Vahrenberg
;; date: 02/03/16

(use-modules (ice-9 debugging traps) (ice-9 debugging trace))

;; from http://stackoverflow.com/questions/5404707/check-if-an-argument-is-a-list-or-an-atom
;; returns true if x is a number, string, etc, and false for lists, pairs, etc
(define (atom? x) (not (or (pair? x) (null? x))))

(define (sum* ttup)
	(if (null? ttup) 0 ;; if null return 0
		(if (atom? (car ttup)) (car ttup) ;; if the car is a leaf node (atom) return its value
			(+ (sum* (car ttup)) (sum* (cdr ttup))) ;; otherwise sum the two branches recursively
		)
	)
)		


;; tests!
(display (sum* '((5)) ))
(display "\n")

(display (sum* '((0) ((0) ((5))) ((0) ((10)))) ))
(display "\n")

(display (sum* '((0) ((0) ((5) ((7)))) ((0) ((10) ))) ))
(display "\n")

(display (sum* '((0) ((0) ((5) ((7) ) ((8) ))) ((0) ((10) ))) ))
(display "\n")

;; correct output:
;;   $ guile d6.scm
;;   5
;;   15
;;   22
;;   30

