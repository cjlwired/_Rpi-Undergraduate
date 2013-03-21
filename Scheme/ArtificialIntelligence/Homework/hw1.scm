;; Carlos Lazo
;; 9-18-06
;; Artificial Intelligence
;; Homework #1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Procedure #1 - fibo ;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Define a function called fibo-helper which will be called by the main fibo
;; function. This function will serve to process the recursion for the 
;; Fibonacci Sequence. fibo-helper is only called if n > 2 - It takes three arguments : 

;;     n --> counter used to keep track of recursion
;;     a --> 2nd to last number in the current sequence
;;     b --> last number in the current sequence

;;;;;;;;;;*********************************************************************;;;;;;;;;;;;
;; Once n = 0, return the empty list. Otherwise, add a new element to the beginning      ;;
;; of the list, which is the sum of a & b. Then recursively call the function again with ;;
;; te appropriate variable changes.                                                      ;;
;;;;;;;;;;*********************************************************************;;;;;;;;;;;;

(define (fibo-helper n a b)
  (if (equal? n 0)
      ()
      (cons (+ a b) (fibo-helper (- n 1) b (+ a b)))))

;;;;;;;;;;**************************************************************************;;;;;;;;;;;;
;; Define function fibo, which is the main function of this procedure. Cover the first        ;;
;; two special cases, where n <= 0, 1, or 2 by returning simple lists. If not, then initially ;;
;; add (1 1) to the list and call fibo-helper to carry out the rest of the recursion.         ;;
;;;;;;;;;;**************************************************************************;;;;;;;;;;;;

(define (fibo n)
  (cond
    ((<= n 0)     '()   )
    ((equal? n 1) '(1)  )
    ((equal? n 2) '(1 1))
    (else (cons 1 (cons 1 (fibo-helper (- n 2) 1 1))))))

(newline)

(write "Testing Procedure #1: fibo")
(newline)
(newline)


(fibo 0)
(fibo 1)
(fibo 2)
(fibo 10)
(fibo 20)

(newline)
(newline)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Procedure #2 - remove-duplicates ;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;*************************************************************;;;;;;;;;;;;
;; Define a function called find-duplicates that takes a list and an element.    ;;
;; The function iterates through the list recursively to see if an element is    ;;
;; found or not.  If the element is found within the list, then return true.     ;;
;; If the entire list is searched and the list ends up being null, which implies ;;
;; that the element is unique within the list, then return false.                ;;
;;;;;;;;;;*************************************************************;;;;;;;;;;;;

(define (find-duplicates l elem)
  (cond
    ((null? l)             #f)
    ((equal? (car l) elem) #t)
    (else (find-duplicates (cdr l) elem))))

;;;;;;;;;;************************************************************************;;;;;;;;;;;;
;; Define function remove-duplicates which takes a list as the only parameter.              ;;
;; If the list is null, return an empty list.  Check to see if the first element            ;;
;; in the list is found in any other part of the list. If it's seen elsewhere, then         ;;
;; ignore the 'current' version of it and call remove-duplicates with the rest of the list. ;;
;; If the element is not found, add it to the current list and call remove-duplicates       ;;
;; to the rest of the list.                                                                 ;;
;;;;;;;;;;************************************************************************;;;;;;;;;;;;

(define (remove-duplicates l)
  (cond
    ((null? l) ())
    ((equal? (find-duplicates (cdr l) (car l)) #t) (remove-duplicates (cdr l)))
    (else (cons (car l) (remove-duplicates (cdr l))))))

(write "Testing Procedure #2: remove-duplicates")
(newline)
(newline)

(remove-duplicates '(1 2 3))
(remove-duplicates '(1 2 1))
(remove-duplicates '(1 1 1 1))
(remove-duplicates '(1 2 3 2 1 4 3 9 8 9 2))

(newline)
(newline)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Procedure #3 - transpose  ;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;**************************************************************;;;;;;;;;;;;
;; Define function transpose. The function takes one parameter, a list            ;;
;; of lists. Using a conditional statement, the following happens -->             ;;
;;                                                                                ;;
;; Once the list is empty, return the empty list. Otherwise, begin creating       ;;
;; lists. Using the map operation, take the car of each list within the 'matrix'. ;;
;; This will create a list of all of the first elements. Then take the transpose  ;;
;; of the cdr of the rest of the lists. This will eliminate the first element     ;;
;; from all of the rows within the matrix. Process the matrix recursively until   ;;
;; the base case is evaluated.                                                    ;;
;;;;;;;;;;**************************************************************;;;;;;;;;;;;


(define (transpose l)
  (cond
    ((null? (car l)) ())
    (else (cons (map car l) (transpose (map cdr l))))))

(write "Testing Procedure #3: transpose")
(newline)
(newline)

(transpose '((1 2 3 4) (3 4 5 5)))
(transpose '( (1 2 3) (4 5 6) (7 8 9) ))
(transpose '((1 0 1 1 0 1) (0 0 1 0 0 0)))

(newline)
(newline)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Procedure #4 - ttt-legal-boards  ;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;********************************************;;;;;;;;;;;;
;; Define function base-three-helper, which takes one argument. ;;
;; This function will recursively take an integer n and convert ;;
;; it into base 3 using both the floor and modulus operations.  ;;
;;;;;;;;;;********************************************;;;;;;;;;;;;

(define (base-three-helper n)
  (cond
    ((< n 3) (cons n ()))
    (else (cons (modulo n 3) (base-three (floor (/ n 3)))))))

;;;;;;;;;;*******************************************;;;;;;;;;;;;
;; Define function base-three, which takes one argument.  This ;;
;; function takes one integer, and                             ;;
;;;;;;;;;;*******************************************;;;;;;;;;;;;

(define (base-three n)
  (reverse (base-three-helper n)))

;;;;;;;;;;************************************;;;;;;;;;;;;
;; Define functions that will help with list processing ;;
;;;;;;;;;;************************************;;;;;;;;;;;;

(define (first l)
  (car l))

(define (second l)
  (car (cdr l)))

(define (third l)
  (car (cdr (cdr l))))

(define (fourth l)
  (car (cdr (cdr (cdr l)))))

(define (fifth l)
  (car (cdr (cdr (cdr (cdr l))))))

(define (sixth l)
  (car (cdr (cdr (cdr (cdr (cdr l)))))))

(define (seventh l)
  (car (cdr (cdr (cdr (cdr (cdr (cdr l))))))))

(define (eigth l)
  (car (cdr (cdr (cdr (cdr (cdr (cdr (cdr l)))))))))

(define (ninth l)
  (car (cdr (cdr (cdr (cdr (cdr (cdr (cdr (cdr l))))))))))

;;;;;;;;;;***************************************************************;;;;;;;;;;;;
;; Define a test to check for valid Tic Tac Toe boards in the following positions: ;;
;;;;;;;;;;***************************************************************;;;;;;;;;;;;

(define (win-check l letter)
  (cond
    ((and (= (first l) letter) (= (second l) letter) (= (third l) letter))   1)
    ((and (= (fourth l) letter) (= (fifth l) letter) (= (sixth l) letter))   1)
    ((and (= (seventh l) letter) (= (eigth l) letter) (= (ninth l) letter))  1)
    ((and (= (first l) letter) (= (fourth l) letter) (= (seventh l) letter)) 1)
    ((and (= (second l) letter) (= (fifth l) letter) (= (eigth l) letter))   1)
    ((and (= (third l) letter) (= (sixth l) letter) (= (ninth l) letter))    1)
    ((and (= (first l) letter) (= (fifth l) letter) (= (ninth l) letter))    1)
    ((and (= (third l) letter) (= (fifth l) letter) (= (seventh l) letter))  1)
    (else 0)))

;;;;;;;;;;******************************************************;;;;;;;;;;;;
;; Define two functions that counts how many x's and o's are on the board ;;
;;;;;;;;;;******************************************************;;;;;;;;;;;;

(define (x-count l)
  (cond
    ((null? l) 0)
    ((= (car l) 1) (+ 1 (x-count (cdr l))))
    (else (x-count (cdr l)))))

(define (o-count l)
  (cond
    ((null? l) 0)
    ((= (car l) 2) (+ 1 (o-count (cdr l))))
    (else (o-count (cdr l)))))

;;;;;;;;;;******************************************************;;;;;;;;;;;;
;; Define a function called valid-board that takes five arguments - the   ;;
;; original list, the number of x's on the board, whether x has won, the  ;;
;; number of o's on the board, and whether o has won. Based upon this, it ;;
;; applies certain necessary game rules that must be true for the board   ;;
;; to be considered valid.                                                ;;
;;;;;;;;;;******************************************************;;;;;;;;;;;;

(define (valid-board num-x x-win num-o o-win)
  (or  
   (and (> x-win 0) (= o-win 0) (= num-x (+ num-o 1)))
   (and (> o-win 0) (= x-win 0) (= num-x num-o))
   (and (= x-win o-win 0) (or (= num-x num-o) (= num-x (+ num-o 1))))))

;;;;;;;;;;*****************************************;;;;;;;;;;;;
;; Define function pass-test, which simply calls valid board ;;
;;;;;;;;;;*****************************************;;;;;;;;;;;;

(define (pass-test l)
   (valid-board (x-count l) (win-check l 1) (o-count l)  (win-check l 2)))
  
;;;;;;;;;;*****************************************************************************;;;;;;;;;;;;
;; Define function lengthen-list along with a helper which fills in leading zeros for all lists  ;;
;;;;;;;;;;*****************************************************************************;;;;;;;;;;;;

(define (lengthen-list-helper l len)
  (cond
    ((= len 9) l)
    (else (cons 0 (lengthen-list-helper l (+ 1 len))))))

;;;;;;;;;;*****************************************************************************;;;;;;;;;;;;
;; Define function lengthen-list along with a helper which fills in leading zeros for all lists  ;;
;;;;;;;;;;*****************************************************************************;;;;;;;;;;;;

(define (lengthen-list l)
  (lengthen-list-helper l (length l)))

;;;;;;;;;;***************************************************************;;;;;;;;;;;;
;; Define function ttt-helper, which takes three arguments. This function keeps    ;;
;; track of all valid boards it finds, and uses a counter to find the base case.   ;;
;; Utilizing an integer to create a representation of the board in base three,     ;;
;; the board is checked using the pass-test function to see if it is valid. The    ;;
;; function then calls itself recursively and updates the valid counter if needed. ;;
;;;;;;;;;;***************************************************************;;;;;;;;;;;;

(define (ttt-helper valid-count counter end)
  (cond
    ((= counter end) valid-count)
    (else 
     (cond 
       ((equal? #t (pass-test (lengthen-list (base-three counter)))) 
         (ttt-helper (+ valid-count 1) (+ counter 1) end))
       (else (ttt-helper valid-count  (+ counter 1) end))))))

;;;;;;;;;;****************************************************************;;;;;;;;;;;;
;; Define function ttt-legal-boards, which utilizes its helper function to initiate ;;
;; Tic Tac Toe Board validation. Run for all 3^9 possible boards.                   ;;
;;;;;;;;;;****************************************************************;;;;;;;;;;;;

(define (ttt-legal-boards)
  (ttt-helper 0 0 19683))

(write "Testing Procedure #4: ttt-legal-boards")
(newline)
(newline)

(ttt-legal-boards)

(newline)
(newline)

(write "*I've checked my algorithm over and have done cross-checking between my boards and the number found by Professor Hollinger. My algorithm displays 5448 and not 5478. I'm missing 30 valid boards. All of my functions are commented so you can follow, please let me know if you can find out where and if there is a clear mistake, thanks!")