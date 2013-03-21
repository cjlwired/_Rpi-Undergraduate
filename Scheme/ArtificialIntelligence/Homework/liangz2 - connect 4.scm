;================================================
;Connect-four is a registered trademark of Hasbro
;================================================
;This program tries to come up with an "intelligent" move
;when playing connect-4

;Submitted by: Zhirong Liang  (liangz2@rpi.edu)


;some global variables
;total rows, total columns .....
(define liangz2-row 6)
(define liangz2-col 7)

;It takes too long with a depth 3 in some bad cases

(define liangz2-Maxdepth 2)
(define liangz2-me 1)
(define liangz2-opponent 2)

; =================================
;getmove function
;used minimax to come up with the best move
;getmove will return the column where the next marble will be dropped
;or 1000 means I win, -1000 means I lose

(define liangz2-getmove 
  (lambda (board turn)
    (begin
      
      ;set the glogal variables accordingly 
      (set! liangz2-row (length board))
      (set! liangz2-col (length (car board)))
      (set! liangz2-me turn)
      (set! liangz2-opponent (/ 2 turn))

      ;call minimax to make the next move
      (liangz2-minimax board turn 0 -1000 1000))))

; =================================
;Improved Alpha-beta minimax

(define liangz2-minimax
  (lambda (cstate turn depth al be)
    (let ((states '()) (bestmove 0) (h (liangz2-heuristic cstate turn)))
      (if 
       (or (= h 1000) (= h -1000) (= depth liangz2-Maxdepth)) h 
       (begin
	  
	  ;getnerates all possibles states under the current state
	  (set! states (liangz2-generate-states cstate cstate 0 turn))
	  ;set alpha or beta 
	  (if
	   (= turn liangz2-me)
	   (set! al -1000)
	   (set! be 1000))
	  
	  ;go thru all states
	  (do ((s states (cdr s)) (i 0 (+ i 1)))
	      ((or 
		(null? s)
		(> al be)))
	    (if (not (null? (car s))) 
		(if (= turn liangz2-me)
		    (let ((newal (liangz2-minimax (car s) liangz2-opponent (+ depth 1) al be)))
		      (if (> newal al)
			  (begin
			    (set! al newal)
			    (set! bestmove i))))
		    (let ((newbe (liangz2-minimax (car s) liangz2-me (+ depth 1) al be)))
		      (if (< newbe be)
			  (set! be newbe))))))
	  
	  ;return which column or alpha-beta
	  (if
	   (= depth 0)
	   bestmove
	   (if
	    (= turn liangz2-me)
	    al
	    be)))))))
  
;Support procedures

; =================================
; find-first-zero finds the first element in a list that has the value 0
; and return it's position in the list (starting at 0).
; returns (+ (length ls) 1) if the element is not found!
; Used (by find-last-zero) to find where dropped marble will end up.
;
(define liangz2-find-first-zero
  (lambda (ls)
    (- (length ls) (length (member 0 ls)))))

; =================================
; find-last-zero finds the last zero in a list.
; This assume the list consists of a (possibly null)
; prefix of zeros followed by a (possibly null) suffix of
; things other than zeros. This is used to find where a marble
; should drop to (should end up replacing the last 0 in a column).
; If there are no zeros, this returns -1, otherwise it returns the
; position (starting at 0) of the last zero in the list

(define liangz2-find-last-zero
  (lambda (ls)
    (- (- (length ls) 1) (liangz2-find-first-zero (reverse ls)))))

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
; (list-replaceelem '(a b c) 1 'foo) => (a foo c)
;

(define liangz2-list-replaceelem
  (lambda (l pos newval)
    (if (= pos 0) 
        (cons newval (cdr l))
        (cons (car l) (liangz2-list-replaceelem (cdr l) (- pos 1) newval)))))

; =================================
; nth-row extracts a single row from a board
; (and returns it as a list). 
; board is a game board representation (see above) and n is
; a row number (0 is the top row).
;
(define liangz2-nth-row
  (lambda (board n)
    (let g-row ((ls board))
      (if (null? ls) 
	  ()
	  (cons (list-ref (car ls) n) (g-row (cdr ls)))))))

; =================================
; getsquare extracts and returns a single board element (0, 1 or 2)
; board is a game board representation (see above)
; row and col are the row number and column number
;
(define liangz2-getsquare
  (lambda (board row col)
    (list-ref (list-ref board col) row)))

; =================================
; setsquare sets the value of a single board element
; No check is done to make sure the board element has the value 0!
; board is a game board representation (see above)
; row and col are the row number and column number
; newval is the new value (probably should be 1 or 2)
;
(define liangz2-setsquare
  (lambda (board row col newval)
    (liangz2-list-replaceelem 
     board col 
     (liangz2-list-replaceelem (list-ref board col) row newval))))


; =================================
;generate-states generates the possible states under the current state
;it returns a list containing all the states
;if a column is full, the corresponding state is an empty list	  


(define liangz2-generate-states 
  (lambda (cstemp cs col player)
    (if (null? cstemp)
	'()
	(let ((rowa (liangz2-find-last-zero (car cstemp))))
	  (cons
	   (if (= rowa -1)
	       '()
	       (liangz2-setsquare cs rowa col player))
	   (liangz2-generate-states (cdr cstemp) cs (+ col 1) player))))))

; =================================
; rightdiag extracts a right diagonal from a board.
; right diags start at the bottom and move up and to the right
; board is a game board representation (see above)
; row and col are the starting coordinates of the diagonal
; (the bottom most element is the start)
; 
(define liangz2-rightdiag
  (lambda (board row col)
    (let ((cols (length board))  
	  (rows (length (car board)))
	  (diag ()))
      (do  ( (r row (- r 1))  (c col (+ c 1)))
	  ((or  (< r 0)  (>= c cols)) 
	   diag)
	(set! diag (append diag (list (liangz2-getsquare board r c))))))))


; =================================
; leftdiag extracts a left diagonal from a board
; left diags start at the bottom and move up and to the left
; row and col are the starting coordinates of the diagonal
(define liangz2-leftdiag
  (lambda (board row col)
    (let ((cols (length board))
	  (rows (length (car board)))
	  (diag ()))
      (do  ( (r row (- r 1))  (c col (- c 1)))
	  ((or  (< r 0)  (< c 0))   diag)
	(set! diag (append diag (list (liangz2-getsquare board r c))))))))


; =================================
; rightdiags returns a list of all the right diagonals
; that include 4 or more elements.
;
(define liangz2-rightdiags
  (lambda (board)
    (let ((diags ()) 
	  (rows (length (car board))) 
	  (cols (length board)))
      (do ((r 3 (+ r 1))) ((= r rows) ())
	(set! diags (cons (liangz2-rightdiag board r 0) diags)))
      (do ((c 1 (+ c 1))) ((= c (- cols 3)) ())
	(set! diags (cons (liangz2-rightdiag board (- rows 1) c) diags)))
      diags)))


; =================================
; leftdiags returns a list of all the left diagonals
; that include 4 or more elements.
;
(define liangz2-leftdiags
  (lambda (board)
    (let ((diags ()) 
	  (rows (length (car board))) 
	  (cols (length board)))
      (do ((c 3 (+ c 1))) ((= c cols) ())
	(set! diags (cons (liangz2-leftdiag board (- rows 1) c) diags)))
      (do ((r (- rows 2) (- r 1))) ((< r 3) ())
	(set! diags (cons (liangz2-leftdiag board r (- cols 1)) diags)))
      diags)))

; =================================
; convert list of columns to list of rows
; Given a board of c columns and r rows,
; the board representation is a list of c elements (one per column),
; each element is a list contains the values for each square in a
; column. This procedure returns a list of r elements (one per row),
; each element is a list containinf the values for each square in 
; a row. 

(define liangz2-board-transpose
  (lambda (board)
    (let ((bt ())   (len (length (car board))))
      (do ( (i (- len 1) (- i 1))) ((< i 0) bt)
	(set! bt (cons (liangz2-nth-row board i) bt))))))

; =================================
; getall extracts all rows, columns and diagonals and makes a big list.
; each element of the list could contain 4 in a row.

(define liangz2-getall
  (lambda (board)
    (append
        board                    ; board holds the columns
	(liangz2-board-transpose board)  ; the rows
	(liangz2-rightdiags board)       ; the diagonals
	(liangz2-leftdiags board))))

; =================================
;to determine if subl is the first subset of l

(define liangz2-first-member?
  (lambda (subl l)
    (cond ((null? subl) #t)
	  ((null? l) #f)
	  ((equal? (car subl) (car l)) (liangz2-first-member? (cdr subl) (cdr l)))
	  (else #f))))

; =================================
;to determine is subl is a subset of l

(define liangz2-member?
  (lambda (subl l)
    (cond ((> (length subl) (length l)) #f)	  
	  ((liangz2-first-member?  subl l) #t)
	  (else (liangz2-member? subl (cdr l)))))) 

; =================================
;to evaluate a row/column/diag, points will be given accordingly

(define liangz2-evaluate-row
  (lambda (row e)
    (cond ((liangz2-member? (list e e e e) row) 1000)
	  ((liangz2-member? (list 0 e e e 0) row) 30)
	  ((liangz2-member? (list 0 e e 0) row) 20)
	  ((liangz2-member? (list 0 e e e) row) 6)
	  ((liangz2-member? (list e e e 0) row) 6)
	  ((liangz2-member? (list e e 0 0) row) 6)
	  ((liangz2-member? (list 0 0 e e) row) 6)
	  (else 0))))

; =================================
;to evaluate all rows, columns, diags, and sum up all the points

(define liangz2-evaluate-all
  (lambda (l e count)
    (if (or (>= count 1000) (null? l)) count
	(liangz2-evaluate-all (cdr l) e (+ count (liangz2-evaluate-row (car l) e))))))



; =================================
;to return a heuristic value for a given state

(define liangz2-heuristic
  (lambda (cs turn)
    (let* ((l (liangz2-getall cs))
	   (h-me (liangz2-evaluate-all l liangz2-me 0))
	   (h-opponent (liangz2-evaluate-all l liangz2-opponent 0)))
      (cond ((>= h-me 1000) 1000)
	    ((>= h-opponent 1000) -1000)
	    (else (- h-me h-opponent))))))


































