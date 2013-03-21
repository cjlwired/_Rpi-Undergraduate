;;Carlos Lazo
;;9-15-04
;;Problem Solving in Computer Science
;; Homework #2 - Graphic 1
;;
;; Function definition -> (drawStar position length color)
;;
;; Use: This function will read in a position, a length, and a color.
;;      Utilizing that one position, it will then proced to draw 
;;      6 different lines circulating around the center of the position,
;;      each line of a certain 'length'. Of course, these lines will be drawn
;;      in the color inputed in the function.
;;
;; Sample Usage:
;;    (drawStar (make-posn 150 150) 20 'yellow)
;;    (drawStar (make-posn 100 300) 50 'green)
;;
;; Please make sure that you are aware that to use this function, you will
;; need to add the teachpack draw.ss; also, make sure that the start function
;; has been called before calling the function.

(define (drawStar point length color)
  (and
   (draw-solid-line 
    (make-posn (+ (posn-x point) length)(posn-y point)) (make-posn (- (posn-x point) length)(posn-y point)) color)
   (draw-solid-line
    (make-posn (- (posn-x point) length)(posn-y point)) (make-posn (posn-x point) (+ (posn-y point) (* 1.5 length))) color)
   (draw-solid-line
    (make-posn (+ (posn-x point) length)(posn-y point)) (make-posn (posn-x point) (+ (posn-y point) (* 1.5 length))) color)
   (draw-solid-line 
    (make-posn (- (posn-x point) length) (+ (posn-y point) length)) (make-posn (+ (posn-x point) length) (+ (posn-y point) length)) color)
   (draw-solid-line 
    (make-posn (- (posn-x point) length) (+ (posn-y point) (/ length 2) (/ length 2))) (make-posn (posn-x point)(- (posn-y point)(/ length 2))) color)
   (draw-solid-line 
    (make-posn (+ (posn-x point) length) (+ (posn-y point) (/ length 2) (/ length 2))) (make-posn (posn-x point)(- (posn-y point)(/ length 2))) color)))
 
;; Creating many different stars here of different colors

(start 500 500)
(drawStar (make-posn 100 100) 50 'blue)
(drawStar (make-posn 200 200) 200 'red)
(drawStar (make-posn 300 100) 50 'green)