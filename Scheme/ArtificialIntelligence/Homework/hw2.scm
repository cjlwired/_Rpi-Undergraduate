;; Carlos Lazo
;; 10-2-2006
;; Artificial Intelligence
;; Homework #2

;; NOTE --> This was done using a lot of Professor Hollinger's BFS code.

;; NOTE -->

;; The following is my state representation

;; STATE ===> (state_depth first_jug second_jug third_jug english_parent_instruction)
;; All states are immediately assigned parent states.

;;;;;-----------------------------;;;;;
;;;;; DEFINE GLOBAL JUG VARIABLES ;;;;;
;;;;;-----------------------------;;;;;

;; Define variables that will store size for all three jugs.

(define jug0-limit 0)
(define jug1-limit 0)
(define jug2-limit 0)

;; Define variable to store goal state of function.

(define goal-state '())

;; Define maximum search depth.

(define max-depth 0)

;; Define a second copy to always keep track of actual max-depth for DFS.

(define final-max-depth 0)

;;;;;----------------------------------------;;;;;
;;;;; DEFINE TOP LEVEL JUG HELPER FUNCTIONS  ;;;;;
;;;;;----------------------------------------;;;;;

;; Return first element in a list.

(define (first l)
  (car l))

;; Return second element in a list.

(define (second l)
  (cadr l))

;; Return third element in a list.

(define (third l)
  (caddr l))

;; Return fourth element in a list.

(define (fourth l)
  (cadddr l))

;; Return fifth element in a list.

(define (fifth l)
  (car (cddddr l)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Develop state formulas for the twelve different jug scenarios ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Scenario 1 - Fill Jug 0

(define (scenario-one state)
  (cons (+ 1 (car state)) (cons jug0-limit (cons (third state) (cons (fourth state) (cons "Fill Jug 0." ()))))))

;; Scenario 2 - Fill Jug 1

(define (scenario-two state)
  (cons (+ 1 (car state)) (cons (second state) (cons jug1-limit (cons (fourth state) (cons "Fill Jug 1." ()))))))

;; Scenario 3 - Fill Jug 2

(define (scenario-three state)
  (cons (+ 1 (car state)) (cons (second state) (cons (third state) (cons jug2-limit (cons "Fill Jug 2." ()))))))

;; Scenario 4 - Empty Jug 0
 
(define (scenario-four state)
  (cons (+ 1 (car state)) (cons 0 (cons (third state) (cons (fourth state) (cons "Empty Jug 0." ()))))))

;; Scenario 5 - Empty Jug 1

(define (scenario-five state)
  (cons (+ 1 (car state)) (cons (second state) (cons 0 (cons (fourth state) (cons "Empty Jug 1." ()))))))

;; Scenario 6 - Empty Jug 2

(define (scenario-six state)
  (cons (+ 1 (car state)) (cons (second state) (cons (third state) (cons 0 (cons "Empty Jug 2." ()))))))

;; Scenario 7 - Pour Jug 0 into Jug 1

(define (scenario-seven state)
  (cons (+ 1 (car state)) (cons 
                           (if (> (- jug1-limit (third state)) (second state)) 0 (- (second state) (- jug1-limit (third state))))
                           (cons 
                            (if (> (- jug1-limit (third state)) (second state)) (+ (second state) (third state)) jug1-limit) 
                            (cons (fourth state) (cons "Pour Jug 0 into Jug 1." ()))))))

;; Scenario 8 - Pour Jug 0 into Jug 2

(define (scenario-eight state)
  (cons (+ 1 (car state)) (cons 
                           (if (> (- jug2-limit (fourth state)) (second state)) 0 (- (second state) (- jug2-limit (fourth state))))
                           (cons (third state) (cons 
                             (if (> (- jug2-limit (fourth state)) (second state)) (+ (second state) (fourth state)) jug2-limit) (cons "Pour Jug 0 into Jug 2." ()))))))

;; Scenario 9 - Pour Jug 1 into Jug 0

(define (scenario-nine state)
  (cons (+ 1 (car state)) (cons 
                           (if (> (- jug0-limit (second state)) (third state)) (+ (third state) (second state)) jug0-limit)
                           (cons 
                            (if (> (- jug0-limit (second state)) (third state)) 0 (- (third state) (- jug0-limit (second state))))
                             (cons (fourth state) (cons "Pour Jug 1 into Jug 0." ()))))))

;; Scenario 10 - Pour Jug 1 into Jug 2

(define (scenario-ten state)
  (cons (+ 1 (car state)) (cons (second state) (cons
                           (if (> (- jug2-limit (fourth state)) (third state)) 0 (- (third state) (- jug2-limit (fourth state))))
                           (cons 
                             (if (> (- jug2-limit (fourth state)) (third state)) (+ (third state) (fourth state)) jug2-limit) (cons "Pour Jug 1 into Jug 2." ()))))))

;; Scenario 11 - Pour Jug 2 into Jug 0

(define (scenario-eleven state)
  (cons (+ 1 (car state)) (cons 
                           (if (> (- jug0-limit (second state)) (fourth state)) (+ (fourth state) (second state)) jug0-limit)
                           (cons (third state) (cons
                            (if (> (- jug0-limit (second state)) (fourth state)) 0 (- (fourth state) (- jug0-limit (second state))))
                             (cons "Pour Jug 2 into Jug 0." ()))))))

;; Scenario 12 - Pour Jug 2 into Jug 1

(define (scenario-twelve state)
  (cons (+ 1 (car state)) (cons (second state) (cons
                           (if (> (- jug1-limit (third state)) (fourth state)) (+ (fourth state) (third state)) jug1-limit)
                           (cons
                            (if (> (- jug1-limit (third state)) (fourth state)) 0 (- (fourth state) (- jug1-limit (third state))))
                             (cons "Pour Jug 2 into Jug 1." ()))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Create successor states from the given state, check for all possible jug rules. ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (successor state)
  (if (< (car state) max-depth)
      (clean-successor
       (list
        (if (not (equal? (second state) jug0-limit))
            (scenario-one state)   #f) 
        (if (not (equal? (third state)  jug1-limit))
            (scenario-two state)   #f)
        (if (not (equal? (fourth state) jug2-limit))
            (scenario-three state) #f)
        (scenario-four state)
        (scenario-five state)
        (scenario-six state)
        (if (and (not (equal? (second state) 0)) (not (equal? (third state)  jug1-limit)))
            (scenario-seven state)   #f)
        (if (and (not (equal? (second state) 0)) (not (equal? (fourth state)  jug2-limit)))
            (scenario-eight state)   #f)
        (if (and (not (equal? (third state) 0)) (not (equal?  (second state)  jug0-limit)))
            (scenario-nine state)   #f)
        (if (and (not (equal? (third state) 0)) (not (equal?  (fourth state)  jug2-limit)))
            (scenario-ten state)   #f)
        (if (and (not (equal? (fourth state) 0)) (not (equal? (second state)  jug0-limit)))
            (scenario-eleven state)   #f)
        (if (and (not (equal? (fourth state) 0)) (not (equal?  (third state)  jug1-limit)))
            (scenario-twelve state)   #f))
      
       ) '()))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Function defined to remove all #f from the successor generated list. ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (clean-successor l)
  (cond 
    ((null? l) '())
    ((equal? (car l) #f) (clean-successor (cdr l)))
    (else (cons (car l) (clean-successor (cdr l))))))

;; Left code as is.

(define show 
  (lambda x
    (map display x)))

;; Left code as is.

(define parentlist ())

(define (parentlist-init)
  (set! parentlist ()))

(define (parentlist-add! child parent)
  ;(show "Adding (" child "  " parent ") to parentlist\n")
  (set! parentlist (cons (list child parent) parentlist)))

;; Left code as is.

(define (parentlist-member? child)
  (let ((alistelem (assoc child parentlist)))
	(if alistelem
		(cadr alistelem)
		#f)))


;; Changed code to only print out the steps, which is the fifth element in a goal state.

(define (getpath x)
  (let ((parent (parentlist-member? x)))
	(cond
	 ;; if we didn't find x in the parentlist, something is wrong
	 ((not parent) (show "huh? a state with no parent?\n"))
	 ;; if we found the start state, we are done.
	 ((equal? parent 'start)
	  (list x))
	 (else
	  ;; create a list from the parent back to the goal, 
	  ;; and add this state at the end of that list
	  (begin
		(append (getpath parent) (list (fifth x))))))))

;; Left as is.

(define (unique-successor x)
  (let us-helper ((s (successor x)) (uniquestates ()))
	(if (null? s)
		uniquestates
		  (if (not (parentlist-member? (car s)))
			  ;; we found a unique state, add to the list
			  ;; we will return (uniquestates)
			  (begin
				(parentlist-add! (car s) x)
				(us-helper (cdr s) (cons (car s) uniquestates)))
			  ;; we found the state in parentlist, don't
			  ;; add to the list of states we will return
			  (us-helper (cdr s) uniquestates)))))

;; ************************************************************* ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Breadth First Search Water Jug Procedure  ;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ************************************************************* ;;

;; Modified BFS code to check for new goal orientation.  I commented out the print statements for easier reading.

(define (bfs startnum goal)
  (parentlist-init )
  (parentlist-add! startnum 'start)
  (let bfs-helper ((states (list startnum)))
	(if (null? states)
		(write "No solution found!")
		(let ((nextstate (car states)))
		  ;(show "state: " nextstate "\n")
		  (if (and (= (second nextstate) (first goal-state)) (= (third nextstate) (second goal-state)) (= (fourth nextstate) (third goal-state)))
			  (begin
				(show "GOAL FOUND, take the following steps to reach solution:" "\n")
				(write (cdr (getpath nextstate))))
			  (begin
				(bfs-helper (append (cdr states) (unique-successor nextstate)))))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; bfswj function is called. It sets global variables which are used by all functions ;;
;; and calls the bfs function to begin the searching.                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (bfswj jug-list goal depth)
  (begin
    (set! jug0-limit  (first jug-list))
    (set! jug1-limit (second jug-list))
    (set! jug2-limit  (third jug-list))
    (set! goal-state goal)
    (set! max-depth depth)
    (bfs '(1 0 0 0 'start) goal)))

(write "*** TESTING OUT BFSWF function ***")
(newline)
(newline)

(bfswj '(3 4 10) '(0 2 0) 10)

(newline)
(newline)

(bfswj '(2 2 2) '(1 1 1) 10)

(newline)
(newline)

(bfswj '(1 2 3) '(1 1 1) 10)

(newline)
(newline)

(bfswj '(3 4 10) '(1 2 0) 10)

(newline)
(newline)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;  Depth First Search Water Jug Procedure  ;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Modified DFS code to check for new goal orientation.  I commented out the print statements for easier reading.

(define (dfs startnum goal)
  (parentlist-init )
  (parentlist-add! startnum 'start)
  (let dfs-helper ((states (list startnum)))
	(if (null? states)
		#f
		(let ((nextstate (car states)))
		  ;(show "state: " nextstate "\n")
		  (if (and (= (second nextstate) (first goal-state)) (= (third nextstate) (second goal-state)) (= (fourth nextstate) (third goal-state)))
			  (begin
				(show "GOAL FOUND, take the following steps to reach solution:" "\n")
				(write (cdr (getpath nextstate)))
                                #t)
			  (begin
				(dfs-helper (append (cdr states) (unique-successor nextstate)))))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Create iterative function that will keep increasing depth by one until it reaches the   ;;
;; maximum depth limit. This is done by updating a global variable and recursively calling ;;
;; the function until the max-depth = final-max-depth.                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (dfswj-iter state goal)
  (cond
    ((= max-depth final-max-depth) (write "No solution found!"))
    ((equal? (dfs state goal) #t) (newline))
    (else 
     (begin
       (set! max-depth (+ max-depth 1))
       (dfswj-iter state goal)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; dfswj function is called. It sets global variables which are used by all functions    ;;
;; and calls the dfs-helper which will run the dfs-iter function to begin the searching. ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (dfswj jug-list goal depth)
  (begin
    (set! jug0-limit  (first jug-list))
    (set! jug1-limit (second jug-list))
    (set! jug2-limit  (third jug-list))
    (set! goal-state goal)
    (set! max-depth 1)
    (set! final-max-depth depth)
    (dfswj-iter '(1 0 0 0 'start) goal)))

(write "*** TESTING OUT DFSWJ function ***")
(newline)
(newline)

(dfswj '(3 4 10) '(0 2 0) 10)

(newline)
(newline)

(dfswj '(2 2 2) '(1 1 1) 10)

(newline)
(newline)

(dfswj '(1 2 3) '(1 1 1) 10)

(newline)
(newline)

(dfswj '(3 4 10) '(1 2 0) 10)

(newline)
(newline)

(dfswj '(23 24 11) '(0 13 0) 10)

