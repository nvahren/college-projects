;; this is how to load external modules in scheme
(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp16/scheme_dailies/d1/paradigms_d1.scm")
(use-modules (ice-9 paradigms_d1))

;; Nathan Vahrenberg

;; the list q
;; notice it has a ' in front of the list; that tells the interpreter to read
;; the list literally (e.g., as atoms, instead of functions)
(define q '(turkey (gravy) (stuffing potatoes ham) peas))

;; question 1
(display "question 1: ")
(display (atom? (car (cdr (cdr q)))))
(display "\n")
;; output: #f
;;
;; explanation:
;; 
;; after the innermost cdr the list is ((gravy) (stuffing potatoes ham) peas))
;; after the next cdr the list is      ((stuffing potatoes ham) peas))
;; the car of the above list is        (stuffing potatoes ham)
;; and so the output of "atom?" is false because the above list is not an atom


;; question 2
(display "question 2: ")
(display (lat? (car (cdr (cdr q)))))
(display "\n")
;; output: #t
;;
;; explanation:
;;
;; after the first cdr the list is ((gravy) (stuffing potatoes ham) peas))
;; after the next cdr the list is  ((stuffing potatoes ham) peas))
;; the car of the above list is    (stuffing potatoes ham)
;; and lat? returns true because this is a list of atoms


;; question 3
(display "question 3: ")
(display (cond ((atom? (car q)) (car q)) (else '())))
(display "\n")
;; output: turkey
;;
;; explanation:
;;
;; the car of q is "turkey"
;; which is an atom, and so the "cond" evaluates the first and only "then" conditions 
;; therefore the output is the car of q, "turkey"

