;; Carlos Lazo
;; 9-16-04
;; Problem Solving in Computer Science Quiz #2
;;
;; Contract :
;;              draw-sqaure: posn number symbol -> graphic
;;              draw-2squares: posn number symbol symbol -> graphic
;;              draw-2x2: posn number symbol symbol -> graphic
;;              draw-4x4: posn number symbol symbol -> graphic
;;              draw-8x8: posn number symbol symbol -> graphic
;;
;; Purpose - The purpose of this program is to ultimately draw a checkboard. To accomplish this, a hierarchy of functions will be built. The function on
;;           the top of the hierarchy will call the function below it, which will then proceed to call the one before, etc. Using this method, it will 
;;           accomplish printing out the checkerboard in a more organized and concise manner. 
;;
;; Example - (draw-8x8 (make-posn 50 50) 30 'red 'black)

(define (draw-sqaure point length color)
  {draw-solid-rect (make-posn (posn-x point) (posn-y point)) length length color})

(define (draw-2squares point length color1 color2)
  (and
   (draw-sqaure point length color1)
   (draw-sqaure (make-posn (+ (posn-x point) length) (posn-y point)) length color2)))

(define (draw-2x2 point length color1 color2)
  (and
   (draw-2squares point length color1 color2)
   (draw-2squares (make-posn (posn-x point)(+ (posn-y point) length)) length color2 color1)))
  
(define (draw-4x4 point length color1 color2)
  (and
   (draw-2x2 point length color1 color2)
   (draw-2x2 (make-posn (posn-x point) (+ (posn-y point) (* 2 length))) length color1 color2)
   (draw-2x2 (make-posn (+ (posn-x point) (* 2 length)) (posn-y point)) length color1 color2)
   (draw-2x2 (make-posn (+ (posn-x point) (* 2 length)) (+ (posn-y point) (* 2 length))) length color1 color2)))

(define (draw-8x8 point length color1 color2)
  (and
   (draw-4x4 point length color1 color2)
   (draw-4x4 (make-posn (posn-x point) (+ (posn-y point) (* 4 length))) length color1 color2)
   (draw-4x4 (make-posn (+ (posn-x point) (* 4 length)) (posn-y point)) length color1 color2)
   (draw-4x4 (make-posn (+ (posn-x point) (* 4 length)) (+ (posn-y point) (* 4 length))) length color1 color2)))


(start 500 500)

;;(draw-sqaure (make-posn 100 100) 50 'red)
;;(draw-2squares (make-posn 100 100) 50 'red 'black)
;;(draw-2x2 (make-posn 100 100) 50 'red 'black)
;;(draw-4x4 (make-posn 100 100) 20 'red 'black)
(draw-8x8 (make-posn 50 50) 30 'red 'black)