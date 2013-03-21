;; Carlos Lazo
;; 9-15-04
;; Problem Solving in Computer Science
;; Homework #2 - Graphic 2
;;
;; Function definition -> (drawShape position length decay choice color color)
;;
;; Use: This function will read in a position, a length, two integers, and two colors.
;;      Utilizing that one position, it will then proceed to draw one shape
;;      that is dependant on the first integer that is sent. This function will be recursive,
;;      drawing in inscribed circle and a rectangle every other time with a shrinking length
;;      every time the function is called. The decay sent is the integer that will be used
;;      to determine the amount that the radius decreases every recursive call.
;;
;; Sample Usage:
;;    (drawShape (make-posn 150 150) 100 3 0 'yellow 'black)
;;    (drawShape (make-posn 100 300) 100 3 1 'red 'green)
;;
;; Please make sure that you are aware that to use this function, you will
;; need to add the teachpack draw.ss; also, make sure that the start function
;; has been called before calling the function
;;
;; NOTE : Depending on the choice you send during the call, either 0 or 1, you can change whether
;; it draws the sqaure first or the circle first for the outer shape. By adding more conditional statements
;; along with draw functions, it is possible to aggregate more figures to the recursive function. Also,
;; 

(define (drawShape point length  decay choice color1 color2)
 (cond
   [(< length 0) true]
   [(= choice 0)
    (and
     {draw-solid-line
      (make-posn (- (posn-x point) length) (- (posn-y point) length)) (make-posn (+ (posn-x point) length) (- (posn-y point) length)) color1}
     (draw-solid-line
      (make-posn (+ (posn-x point) length) (- (posn-y point) length)) (make-posn (+ (posn-x point) length) (+ (posn-y point) length)) color1)
     (draw-solid-line
      (make-posn (+ (posn-x point) length) (+ (posn-y point) length)) (make-posn (- (posn-x point) length) (+ (posn-y point) length)) color1)
     (draw-solid-line
      (make-posn (- (posn-x point) length) (+ (posn-y point) length)) (make-posn (- (posn-x point) length) (- (posn-y point) length)) color1)
     (drawShape point (- length decay) decay 1 color1 color2))]
   [(= choice 1)
    (and
     (draw-circle point length color2)
     (drawShape point (- length decay) decay 0 color1 color2))]
   ))

(start 1000 1000)
(drawShape (make-posn 500 500) 500 3 0 'black 'aqua) 
;;(drawShape (make-posn 500 500) 375 3 1 'gray 'orange)
;;(drawShape (make-posn 500 500) 250 3 0 'blue 'green)
;;(drawShape (make-posn 500 500) 125 3 1 'purple 'yellow)