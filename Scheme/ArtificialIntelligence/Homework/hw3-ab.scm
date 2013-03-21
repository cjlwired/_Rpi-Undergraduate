;; Carlos Lazo
;; 10-26-06
;; Artificial Intelligence
;; Homework #3 - Connect Four Player

;; Must be included for random numbers to be enabled.

(#%require (only mzscheme random))

;; *********************************************** ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Static Evaluation Function  ;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; *********************************************** ;;

;; NOTE : Function value of 1000 = WIN, Function value of -1000 = LOSS
;;        Function value of 0 = symmetrical board according to evaluation function.


;; First define all necessary support functions.
;; The code contained in the *** is taken from Dave's sample code.

;; ********************************************************************* ;;
;; ********************************************************************* ;;

; =================================
; lazoc-nth-row extracts a single row from a board
; (and returns it as a list). 
; board is a game board representation (see above) and n is
; a row number (0 is the top row).
;


(define lazoc-nth-row
  (lambda (board n)
    (let g-row ((ls board))
      (if (null? ls) 
	  ()
	  (cons (list-ref (car ls) n) (g-row (cdr ls)))))))

; =================================
; lazoc-getsquare extracts and returns a single board element (0, 1 or 2)
; board is a game board representation (see above)
; row and col are the row number and column number
;
(define lazoc-getsquare
  (lambda (board row col)
    (list-ref (list-ref board col) row)))


; =================================
;
; list-replaceelem modifies a list by setting the specified
; list element to a new value, and returns the new list.
; parameters are l (the list), pos the position of the element to
; be changed: 0 is the first element (the car), etc.
; newval is the value the new element shoudl take.
;
; example - this replaces the value of position 1 in the
; list '(a b c) with the value 'foo:
; (lazoc-list-replaceelem '(a b c) 1 'foo) => (a foo c)
;

(define lazoc-list-replaceelem
  (lambda (l pos newval)
    (if (= pos 0) 
        (cons newval (cdr l))
        (cons (car l) (lazoc-list-replaceelem (cdr l) (- pos 1) newval)))))

; =================================
; lazoc-setsqaure sets the value of a single board element
; No check is done to make sure the board element has the value 0!
; board is a game board representation (see above)
; row and col are the row number and column number
; newval is the new value (probably should be 1 or 2)
;
(define lazoc-setsqaure
  (lambda (board row col newval)
    (lazoc-list-replaceelem 
     board col 
     (lazoc-list-replaceelem (list-ref board col) row newval))))



; =================================
; rightdiag extracts a right diagonal from a board.
; right diags start at the bottom and move up and to the right
; board is a game board representation (see above)
; row and col are the starting coordinates of the diagonal
; (the bottom most element is the start)
;
(define lazoc-rightdiag
  (lambda (board row col)
    (let ((cols (length board))  
	  (rows (length (car board)))
	  (diag ()))
      (do  ( (r row (- r 1))  (c col (+ c 1)))
	  ((or  (< r 0)  (>= c cols)) 
	   diag)
	(set! diag (append diag (list (lazoc-getsquare board r c))))))))

; =================================
; leftdiag extracts a left diagonal from a board
; left diags start at the bottom and move up and to the left
; row and col are the starting coordinates of the diagonal

(define lazoc-leftdiag
  (lambda (board row col)
    (let ((cols (length board))
	  (rows (length (car board)))
	  (diag ()))
      (do  ( (r row (- r 1))  (c col (- c 1)))
	  ((or  (< r 0)  (< c 0))   diag)
	(set! diag (append diag (list (lazoc-getsquare board r c))))))))

; =================================
; lazoc-rightdiags returns a list of all the right diagonals
; that include 4 or more elements.
;
(define lazoc-rightdiags
  (lambda (board)
    (let ((diags ()) 
	  (rows (length (car board))) 
	  (cols (length board)))
      (do ((r 3 (+ r 1))) ((= r rows) ())
	(set! diags (cons (lazoc-rightdiag board r 0) diags)))
      (do ((c 1 (+ c 1))) ((= c (- cols 3)) ())
	(set! diags (cons (lazoc-rightdiag board (- rows 1) c) diags)))
      diags)))


; =================================
; leftdiags returns a list of all the left diagonals
; that include 4 or more elements.
;
(define lazoc-leftdiags
  (lambda (board)
    (let ((diags ()) 
	  (rows (length (car board))) 
	  (cols (length board)))
      (do ((c 3 (+ c 1))) ((= c cols) ())
	(set! diags (cons (lazoc-leftdiag board (- rows 1) c) diags)))
      (do ((r (- rows 2) (- r 1))) ((< r 3) ())
	(set! diags (cons (lazoc-leftdiag board r (- cols 1)) diags)))
      diags)))

; =================================
; convert list of columns to list of rows
; Given a board of c columns and r rows,
; the board representation is a list of c elements (one per column),
; each element is a list contains the values for each square in a
; column. This procedure returns a list of r elements (one per row),
; each element is a list containinf the values for each square in 
; a row. 

(define lazoc-boardtranspose
  (lambda (board)
    (let ((bt ())   (len (length (car board))))
      (do ( (i (- len 1) (- i 1))) ((< i 0) bt)
	(set! bt (cons (lazoc-nth-row board i) bt))))))

; =================================
; lazoc-getall extracts all rows, columns and diagonals and makes a big list.
; each element of the list could contain 4 in a row.

(define lazoc-getall
  (lambda (board)
    (append
        board                    ; board holds the columns
	(lazoc-boardtranspose board)  ; the rows
	(lazoc-rightdiags board)       ; the diagonals
	(lazoc-leftdiags board))))

; =================================
; four-in-a-row? is a predicate that returns true if a list contains
; 4 consecutive elements that all match a single value.
; l is the list (could be from a row, column or diaganol) and
; e is the value we are looking for (1 or 2)  
;
(define four-in-a-row?
  (lambda (l e)
    (let finar ((ls l) (count 0))
      ; if we don't have enough elements left to make 4 in a row - FALSE
      (if (< (+ count (length ls)) 4)
	  #f
	  (if (= e (car ls))
	      ; we got a match
	      (if (= count 3)
		  #t            ; 4 in a row!
		  (finar (cdr ls) (+ count 1)))
	      ; no match
	      (finar (cdr ls) 0))))))

;; ********************************************************************* ;;
;; ********************************************************************* ;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Define global variables ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define lazoc-player 0)
(define lazoc-other 0)

(define lazoc-p_one 0)
(define lazoc-p_two 0)
(define lazoc-p_three 0)
(define lazoc-o_one 0)
(define lazoc-o_two 0)
(define lazoc-o_three 0)

(define lazoc-extract-board '())

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Define helper functions ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Function win-check checks to see if there is a win in the 
;; listed row utilizing the four-in-a-row? function.

(define (lazoc-win-check l p)
  (cond
    ((null? l) #f)
    ((equal? (four-in-a-row? (car l) p) #t) #t)
    (else (lazoc-win-check (cdr l) p))))

;; Function count-first-elem and helper is used to find the first player piece found
;; in each column. This value will be added to the global variables.

(define (lazoc-cfe-helper l)
  (cond
    ((null? l) 0)
    ((equal? (car l) lazoc-player ) (set! lazoc-p_one (+ lazoc-p_one 1)))
    ((equal? (car l) lazoc-other  ) (set! lazoc-o_one (+ lazoc-o_one 1)))
    (else (lazoc-cfe-helper (cdr l)))))

(define (count-first-elem l)
    (cond
      ((null? l) (set! lazoc-p_one lazoc-p_one))
      (else
       (begin
         (lazoc-cfe-helper (car l))
         (count-first-elem (cdr l))))))

;; Function tie-check will see if there is a tie in the game. This is indicated when all
;; columns are full.

(define (lazoc-tie-check board)
  (cond
    ((null? board) #t)
    ((equal? 0 (caar board)) #f)
    (else (lazoc-tie-check (cdr board)))))
  
;; Function two-check and helpers look to find any place where there are two 
;; elements in a row.  Global variables are updated accordingly. Start by 
;; eliminating all leading 0's, then analyzing starting from the top of the 
;; column ensuring a length of atleast 2. Return #t if found and update
;; correct player variable.

(define (lazoc-delete-zero l)
  (cond
    ((null? l) '())
    ((= (car l) 0) (lazoc-delete-zero (cdr l)))
    (else (cons (car l) (lazoc-delete-zero (cdr l))))))

(define (lazoc-twoc-helper l)
  (let ((rm-list (lazoc-delete-zero l)))
        (cond
          ((not (>= (length rm-list) 2)) (set! lazoc-p_two lazoc-p_two))
          (else
           (if (= (car rm-list) (car (cdr rm-list))) 
 
                (if (= (car rm-list) lazoc-player) 
                    (set! lazoc-p_two (+ lazoc-p_two 1))
                    (set! lazoc-o_two (+ lazoc-o_two 1)))
            (set! lazoc-p_two lazoc-p_two))))))

(define (lazoc-two-check l)
  (cond
    ((null? l) (set! lazoc-p_two lazoc-p_two))
    (else
     (begin
       (lazoc-twoc-helper (car l))
       (lazoc-two-check (cdr l))))))

;; Function three-check and helpers look to find any place where there are two 
;; elements in a row.  Global variables are updated accordingly. Start by 
;; eliminating all leading 0's, then analyzing starting from the top of the 
;; column ensuring a length of atleast 3. Return #t if found and update
;; correct player variable.

(define (lazoc-threec-helper l)
  (let ((rm-list (lazoc-delete-zero l)))
        (cond
          ((not (>= (length rm-list) 3)) (set! lazoc-p_three lazoc-p_three))
          (else
           (cond
             ((and (= (car rm-list) lazoc-player) (= (cadr rm-list) lazoc-player) (= (caddr rm-list) lazoc-player)) (set! lazoc-p_three (+ lazoc-p_three 1)))
             ((and (= (car rm-list) lazoc-other) (= (cadr rm-list) lazoc-other) (= (caddr rm-list) lazoc-other)) (set! lazoc-o_three (+ lazoc-o_three 1)))
             (else (set! lazoc-p_three lazoc-p_three)))))))

(define (lazoc-three-check l)
  (cond
    ((null? l) (set! lazoc-p_three lazoc-p_three))
    (else
     (begin
       (lazoc-threec-helper (car l))
       (lazoc-three-check (cdr l))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Board evaluation function ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (lazoc-board-eval b p)
  (begin
    
    ;; Set correct player variables based upon given information.
    
    (if (= p 1)
        (begin
          (set! lazoc-player 1)
          (set! lazoc-other 2))
        (begin
          (set! lazoc-player 2)
          (set! lazoc-other 1)))
    
    ;; Set new board that contains all extracted information.
    
    (display "CURRENT BOARD SENT FOR EVALUATION")
    (newline)    
    (display b)
    (newline)
    (newline)
    
    (set! lazoc-extract-board (lazoc-getall b))
    
    ;; -- Perform board evaluation function --
    
    (cond
      
      ;; First check to see if there are any wins in the board.
      
      ((equal? (lazoc-win-check lazoc-extract-board lazoc-player) #t) 1000)
      ((equal? (lazoc-win-check lazoc-extract-board lazoc-other) #t) -1000)
      
      ;; If there was no instant win, then perform complete analysis of board.
      
      (else
       (begin
         
         ;; Begin by counting all of the top elements in the board and adjusting
         ;; the global variables appropriately.
         
         (count-first-elem b) 
         
         ;; Now look at extracted board rows and search for those containing two elements
         ;; in a row. Update the global variables appropriately.
         
         (lazoc-two-check lazoc-extract-board)
         
         ;; Now look at extracted board rows and search for those containing three elements
         ;; in a row. Update the global variables appropriately.
         
         (lazoc-three-check lazoc-extract-board)
         
         ;; Now that all calculations are done, evaluate the board using the following formula :
         
         ;; BOARD STATE = [(5*lazoc-p_three) + (3*lazoc-p_two) + (1*lazoc-p_one)] - [(5*lazoc-o_three) + (3*lazoc-o_two) + (1*lazoc-o_one)
         
         (- (+ (* 5 lazoc-p_three) (* 3 lazoc-p_two) (* 1 lazoc-p_one)) (+ (* 5 lazoc-o_three) (* 3 lazoc-o_two) (* 1 lazoc-o_one)))
        
        )))
    
    ))

;; ************************************* ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Minimax Function  ;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ************************************* ;;

;; First define all necessary support functions.
;; The code contained in the *** is taken from Dave's sample code.

;; ********************************************************************* ;;
;; ********************************************************************* ;;

; =================================
; lazoc-find-first-zero finds the first element in a list that has the value 0
; and return it's position in the list (starting at 0).
; returns (+ (length ls) 1) if the element is not found!
; Used (by find-last-zero) to find where dropped marble will end up.
;
; CHANGE 10/30/98
; DLH - member returns #f if not found, this is () only with MIT scheme!
(define lazoc-find-first-zero
  (lambda (ls)
    (cond
     ((null? ls) 1)
     ((= (car ls) 0) 0)
     (else (+ 1 (lazoc-find-first-zero (cdr ls)))))))


; =================================
; find-last-zero finds the last zero in a list.
; This assume the list consists of a (possibly null)
; prefix of zeros followed by a (possibly null) suffix of
; things lazoc-other than zeros. This is used to find where a marble
; should drop to (should end up replacing the last 0 in a column).
; If there are no zeros, this returns -1, lazoc-otherwise it returns the
; position (starting at 0) of the last zero in the list

(define lazoc-find-last-zero
  (lambda (ls)
    (- (- (length ls) 1) (lazoc-find-first-zero (reverse ls)))))

; =================================
; makemove applies a move (by dropping a marble in a column)
; to a board and returns the resulting board or #f if the
; move is not valid (column is full)
; board is the current game state
; player is 1 or 2 (the player dropping the marble)
; col is the column number (starting at 0).
;
(define lazoc-makemove
  (lambda (board player col)
    (let ((row (lazoc-find-last-zero (list-ref board col))))
      (if (< row 0)
	  #f                 ; no room left!
	  (lazoc-setsqaure board row col player)))))

;; ********************************************************************* ;;
;; ********************************************************************* ;;

(define lazoc-maxdepth 5)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Define helper functions ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Function possible-moves and its helper take a board and player as an input and 
;; creates a list of all possible boards. This is the successor function. The helper
;; function deletes any values of #f returned from lazoc-getmove.

(define (lazoc-delete-false l)
  (cond
    ((null? l) '())
    ((equal? (car l) #f) (lazoc-delete-false (cdr l)))
    (else (cons (car l) (lazoc-delete-false (cdr l))))))

(define (lazoc-possible-moves board player col)
  (cond
    ((= col (- (length (car board)) 1)) (lazoc-makemove board player col))
    (else (lazoc-delete-false (cons (lazoc-makemove board player col) (lazoc-possible-moves board player (+ col 1)))))))

;; Define check-leaf function that will check to see if the current state is a leaf node of the tree.
;; In lazoc-other words, if there is a win, a loss, or a tie.


(define (lazoc-check-leaf b)
  (let ((leaf-board (lazoc-getall b)))
    (or
     (if (equal? (lazoc-win-check leaf-board lazoc-player) #t) #t #f)
     (if (equal? (lazoc-win-check leaf-board lazoc-other)  #t) #t #f)
     (if (equal? (lazoc-tie-check b) #t) #t #f))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Minmax  Implementation ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define lazoc-minimax
  (lambda (cstate turn depth al be)
    (let ((states '()) (bestmove 0) (h (lazoc-board-eval cstate turn)))
      (if 
       (or (= h 1000) (= h -1000) (= depth lazoc-maxdepth)) h 
       (begin
	  
	  ;getnerates all possibles states under the current state
	  (set! states (lazoc-possible-moves cstate turn 0))
          ;(display states)
          ;(display "DEBUG 1!")
	  ;set alpha or beta 
	  (if
	   (= turn lazoc-player)
	   (set! al -1000)
	   (set! be 1000))
	  
	  ;go thru all states
	  (do ((s states (cdr s)) (i 0 (+ i 1)))
	      ((or 
		(null? s)
		(> al be)))
	    (if (not (null? (car s))) 
		(if (= turn lazoc-player)
		    (let ((newal (lazoc-minimax (car s) lazoc-other (+ depth 1) al be)))
		      (if (> newal al)
			  (begin
			    (set! al newal)
			    (set! bestmove i)
                            (display (car s)))))
		    (let ((newbe (lazoc-minimax (car s) lazoc-player (+ depth 1) al be)))
		      (if (< newbe be)
			  (set! be newbe))))))
	  
	  ;return which column or alpha-beta
	  (if
	   (= depth 0)
	   bestmove
	   (if
	    (= turn lazoc-player)
	    al
	    be)))))))

;; Define get-move function here, which will decide which column to choose in the tournament.

(define (lazoc-getmove b p)
  (begin
    
    ;; Set appropriate lazoc-player configurations for board analysis.
    
    (if (= p 1)
        (begin
          (set! lazoc-player 1)
          (set! lazoc-other 2))
        (begin
          (set! lazoc-player 2)
          (set! lazoc-other 1)))
    
    (lazoc-minimax b p 0 -1000 1000)
    
    ))

(define board 
  '( (0 0 0 2 2 1) (0 0 0 2 1 2)
   (0 0 0 0 2 1) (0 0 0 0 1 2) 
   (0 0 0 1 2 1) (0 0 0 2 1 1)
   (1 2 1 1 2 2) ))

(lazoc-getmove board 1)

;(lazoc-possible-moves board 1 0)