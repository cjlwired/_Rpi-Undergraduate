;; Carlos Lazo
;; 9-30-04
;; PSiCS Quiz #4

;;
;; QUIZ 4 code 
;;

;; Here are the structure definitions for the animation entities supported by draw-anim-entity

;; circle : 
;;     center is a posn
;;     radius is a number
;;     color is a symbol. 'Clear mean clear the circle!

(define-struct circle (center radius color))

;; square : 
;;     center is a posn (NOTE we use center, not topleft!)
;;     radius is a number
;;     color is a symbol. 'Clear means clear the circle

(define-struct square (center size color))

;; delay is just a time in seconds
(define-struct delay (time))



;; draw-anim-entity consumes an animation-entity (a struct that is either
;;    a circle, square or delay
;;
;; For square and circle, either draws or clears the entity (based on the color)
;; For delay, just waits for a while
; 
(define (draw-anim-entity s)
  (cond

    [(circle? s) 
	 ;; it's a circle - should we draw or clear?
	 (cond
	  [ (symbol=? (circle-color s) 'Clear)
		;; clear it
		(clear-circle (circle-center s) (circle-radius s))]

	  [ else
		;; draw it
		(draw-circle (circle-center s) (circle-radius s) (circle-color s)) ])]

    [(square? s) 
	 ;; it's a square - should we draw or clear?
	 (cond
	  [(symbol=? (square-color s) 'Clear)
	   ;; clear it - need to translate from center to topleft
	   (clear-solid-rect 
		(make-posn
		 (- (posn-x (square-center s)) (/ (square-size s) 2))
		 (- (posn-y (square-center s)) (/ (square-size s) 2)))
		(square-size s) (square-size s))]

	  [ else
		;; draw it
		(draw-solid-rect 
		 (make-posn
		  (- (posn-x (square-center s)) (/ (square-size s) 2))
		  (- (posn-y (square-center s)) (/ (square-size s) 2)))
		 (square-size s) (square-size s) (square-color s))])]

	[(delay? s)
	 ;; it's a delay - wait for a while
	 (sleep-for-a-while (delay-time s))]

	;; it's not anything we understand - report an error
    [else 
	 (error 'draw-anim-entity "I dont' know how to draw that (is it an animimation entity?)")]))
;;
;;

;; 
(start 1000 1000)

;;(draw-anim-entity
;; (make-square (make-posn 200 200) 141 'Blue))

;;(draw-anim-entity
;; (make-circle (make-posn 200 200) 100 'Red))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PLAY function definition ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (play alist)
  (cond
    [(empty? alist) false]
    [else
     (and
      (draw-anim-entity (first alist))
      (play (rest alist)))]))

;;(play (cons (make-circle (make-posn 100 100) 20 'Red)
  ;;  (cons (make-delay 0.5)
    ;;   (cons (make-circle (make-posn 100 100) 30 'Red)
      ;;    (cons (make-delay 0.5)
        ;;     (cons (make-circle (make-posn 100 100) 40 'Red)
          ;;      (cons (make-delay 0.5)
            ;;       (cons (make-circle (make-posn 100 100) 50 'Red) empty))))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; GROW-CIRCLE function defintion  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; c is the circle
;; grow is the amount that the radius should be growing each time
;; delay is the amount of delay that should be in the middle of the circle growth
;; step is the amount of times that thisanimation should be drawn.

(define (grow-circle c grow delay step)
  (cond
    [(= step 0) empty]
    [else
      (cons (make-circle (circle-center c) (circle-radius c) (circle-color c))
            (cons (make-delay delay) (grow-circle (make-circle (circle-center c) (+ (circle-radius c) grow) (circle-color c)) grow delay (- step 1))))]))

;;(play
;;  (grow-circle
;;    ;; initial circle
;;	(make-circle (make-posn 400 400) 10 'Blue)
;;	;; amount to grow
;;	2
;;	;; delay per step
;;	0.1
;;	;; total steps
;;	200))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; MERGE FUNCTION DEFINTION ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (merge a b)
  (cond
    [(and (empty? a) (empty? b)) empty]
    [(empty? a) 
     (cons (rest b) empty)]
    [(empty? b)
     (cons (rest a) empty)]
    [else
     (cons (first a)
           (cons (first b) (merge (rest a) (rest b))))]))

;;(play
;;  (merge
;;    ;; red circle at 400,400
;;    (grow-circle
;;        ;; initial circle
;;    	(make-circle (make-posn 400 400) 10 'Red)
;;    	;; amount to grow
;;    	2
;;    	;; delay per step
;;    	0.05
;;    	;; total steps
;;    	200)

;;    ;; blue circle at 200,200
;;    (grow-circle
;;        ;; initial circle
;;    	(make-circle (make-posn 200 200) 2 'Blue)
;;    	;; amount to grow
;;    	1
;;		;; set time to 0 since we are merging
;;      0
;;    	;; total steps
;;    	200)))

;;;;;;;;;;;;;;;;;;;;;
;; EXTRA FUNCTIONS ;;
;;;;;;;;;;;;;;;;;;;;;

(define (grow-square s grow delay step)
  (cond
    [(= step 0) empty]
    [else
      (cons (make-square (square-center s) (square-size s) (square-color s))
            (cons (make-delay delay) (grow-square (make-square (square-center s) (+ (square-size s) grow) (square-color s)) grow delay (- step 1))))]))

;;(play
;;  (grow-square
;;    ;; initial circle
;;	(make-square (make-posn 200 200) 10 'Green)
;;	;; amount to grow
;;	10
;;	;; delay per step
;;	0.05
;;	;; total steps
;;	200))

;;;;;;;;;;;;;;;;;;;;;;
;; DRAWING FUNCTION ;;
;;;;;;;;;;;;;;;;;;;;;;

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'Gold)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	100))

(play
  (merge
    (grow-circle
        ;; initial circle
    	(make-circle (make-posn 250 250) 10 'Red)
    	;; amount to grow
    	2
    	;; delay per step
    	0.05
    	;; total steps
    	200)

    ;; blue circle at 200,200
    (grow-circle
        ;; initial circle
    	(make-circle (make-posn 750 250) 10 'Blue)
    	;; amount to grow
    	2
	;; set time to 0 since we are merging
        0
    	;; total steps
    	200)))

(play
 (merge
  (grow-circle
   ;; initial circle
   (make-circle (make-posn 250 750) 10 'Green)
   ;; amount to grow
   2
   ;; delay per step
   0.05
   ;; total steps
   200)
  
  ;; blue circle at 200,200
  (grow-circle
   ;; initial circle
   (make-circle (make-posn 750 750) 10 'Cyan)
   ;; amount to grow
   2
   ;; set time to 0 since we are merging
   0
   ;; total steps
   200)))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'Silver)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	100))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'Chartreuse)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	90))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'BlanchedAlmond)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	80))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'Peru)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	70))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'DarkGreen)
	;; amount to grow
	10
	;; delay per step
	0.01
	;; total steps
	60))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'DodgerBlue)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	50))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'Firebrick)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	40))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'Gray)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	30))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'GreenYellow)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	20))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 10 'LightCyan)
	;; amount to grow
	10
	;; delay per step
	0.05
	;; total steps
	10))

(play
  (grow-square
    ;; initial circle
	(make-square (make-posn 500 500) 1 'Black)
	;; amount to grow
	10
	;; delay per step
	0.1
	;; total steps
	1000))
