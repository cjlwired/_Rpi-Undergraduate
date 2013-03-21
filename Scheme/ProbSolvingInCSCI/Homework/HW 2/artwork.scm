;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Carlos Lazo
;; 9-20-04
;; Homework #2 - Part II -> Graphic Artwork
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;; FUNCTION #1
;; NOTE : I decided to change this function around because I wanted my canvas size to be 1500 by 500
;;        Also, I wanted to scale it to my prefered size. I got rid of the sun and of the trees, just
;;        leaving the ground and the sky,

;; my-world function creates a background with trees on canvas size 600 600
;; allows for color customization of the sky, ground, tree leaves color and the tree trunk
(define (my-world skycolor groundcolor treecolor trunkcolor)
  (and
  (draw-solid-rect (make-posn 0 0) 1500 800 skycolor)
  (draw-solid-rect (make-posn 0 800) 1500 200 groundcolor)
  ;(draw-solid-disk (make-posn 100 100) 40 'yellow)
  ;(draw-solid-rect (make-posn 62 400) 24 100 trunkcolor)
  ;(draw-solid-rect (make-posn 512 400) 24 100 trunkcolor)
  ;(draw-solid-disk (make-posn 74 400) 50 treecolor)
  ;(draw-solid-disk (make-posn 524 400) 50 treecolor)
  ))

;; FUNCTION #2

(define (draw-sun xpos ypos size rcolor ccolor)
  ;; xpos is the starting x coordinate.
  ;; ypos is the starting y coordinate.
  ;; the sun is centered on (x,y)
  ;; size is the size of the circle of the sun.
  ;; rcolor is the color of the rays coming out of the sun.
  ;; ccolor is the color of the circle the sun is made from .
  (and
   (draw-solid-line (make-posn (- xpos (* 2 size)) ypos) (make-posn (+ xpos (* 2 size)) ypos) rcolor)
   (draw-solid-line (make-posn xpos (- ypos (* 2 size))) (make-posn xpos (+ ypos (* 2 size))) rcolor)
   (draw-solid-line (make-posn (- xpos size) (round (- ypos (* size (sqrt 3))))) (make-posn (+ xpos size) (round (+ ypos (* size (sqrt 3))))) rcolor)
   (draw-solid-line (make-posn (- xpos size) (round (+ ypos (* size (sqrt 3))))) (make-posn (+ xpos size) (round (- ypos (* size (sqrt 3))))) rcolor)
   (draw-solid-line (make-posn (- xpos (round (* size (sqrt 3)))) (- ypos size)) (make-posn (+ xpos (round (* size (sqrt 3)))) (+ ypos size)) rcolor)
   (draw-solid-line (make-posn (- xpos (round (* size (sqrt 3)))) (+ ypos size)) (make-posn (+ xpos (round (* size (sqrt 3)))) (- ypos size)) rcolor)
   ;; these lines of code draws 6 lines that are to be the rays coming out of the sun.
   ;; the lines intersect at the starting position.  
   (draw-solid-disk (make-posn xpos ypos) size ccolor)
   ;; the circle hides the intersection so that the final pictues looks like it has rays coming out of it.
   )
  )

;; FUNCTION #3 (MY FUNCTION)

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

;; FUNCTION #4

;draw-cloud: posn number number symbol symbol -> picture
;purpose is to make a picture of a cloud
;draw outline of cloud, then solid circles to fill in
;draw-cloud pos size color1 color2
;test
;;;(draw-cloud (make-posn 100 75) 20 'skyblue 'paleturquoise)


(define (draw-cloud pos size color1 color2)
  (and
   ;;Top: solid circle, then outlines: 3 in a row to create depth
   (draw-solid-disk
    (make-posn (* (posn-x pos) 4) (* (posn-y pos) 2.5)) (* size 2) color1)
   (draw-circle
    (make-posn (* (posn-x pos) 4.02) (* (posn-y pos) 2.5)) (* size 2) color2)
   (draw-circle
    (make-posn (* (posn-x pos) 4.01) (* (posn-y pos) 2.5)) (* size 2) color2) 
   (draw-circle
    (make-posn (* (posn-x pos) 4.00) (* (posn-y pos) 2.5)) (* size 2) color2)
   ;
   (draw-solid-disk
    (make-posn (* (posn-x pos) 3.5) (* (posn-y pos) 2.5)) (* size 3) color1)  
   (draw-circle
    (make-posn (* (posn-x pos) 3.52) (* (posn-y pos) 2.5)) (* size 3) color2)
   (draw-circle
    (make-posn (* (posn-x pos) 3.51) (* (posn-y pos) 2.5)) (* size 3) color2) 
   (draw-circle
    (make-posn (* (posn-x pos) 3.50) (* (posn-y pos) 2.5)) (* size 3) color2)
    ;
   (draw-solid-disk
    (make-posn (* (posn-x pos) 2.5) (* (posn-y pos) 2.25)) (* size 3.5) color1)
   (draw-circle
    (make-posn (* (posn-x pos) 2.52) (* (posn-y pos) 2.25)) (* size 3.5) color2)
   (draw-circle
    (make-posn (* (posn-x pos) 2.51) (* (posn-y pos) 2.25)) (* size 3.5) color2) 
   (draw-circle
    (make-posn (* (posn-x pos) 2.50) (* (posn-y pos) 2.25)) (* size 3.5) color2)
   
   ;
   (draw-solid-disk
    (make-posn (* (posn-x pos) 1.5) (* (posn-y pos) 2.5)) (* size 4) color1)
   (draw-circle
    (make-posn (* (posn-x pos) 1.52) (* (posn-y pos) 2.5)) (* size 4) color2)
   (draw-circle
    (make-posn (* (posn-x pos) 1.51) (* (posn-y pos) 2.5)) (* size 4) color2) 
   (draw-circle
    (make-posn (* (posn-x pos) 1.50) (* (posn-y pos) 2.5)) (* size 4) color2)
  
   ;bottom circles
   (draw-solid-disk
    (make-posn (* (posn-x pos) 4) (* (posn-y pos) 3)) (* size 3) color2)
   (draw-solid-disk
    (make-posn (* (posn-x pos) 3) (* (posn-y pos) 3)) (* size 4) color2)
   (draw-solid-disk
    (make-posn (* (posn-x pos) 2) (* (posn-y pos) 3)) (* size 3) color2)
   (draw-solid-disk
    (make-posn (* (posn-x pos) 1) (* (posn-y pos) 3)) (* size 4) color2)))

;; FUNCTION #5 (MY FUNCTION)

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

;;FUNCTION #6

;;draw-panda posn number -> boolean boolean
;;
;;Consumes the position of the panda's stomach (type posn) and its size(number) and creates an image of a panda.
;;
;;Unfortunately, the functions that we use to draw require an integer for size. However, since the proportions at points
;;require division by 16, the size needs to be divisible by 16
;
;;before using this function, function start must be called according to the following definition-
;;
;;(start number1 number2) - number1 equals the width of the canvas window while number2 equals the height
;;
;;test -> (draw-panda (make-posn 150 150) 50) -> false (no picture)
;;test -> (draw-panda (make-posn 150 150) 64) -> true true (draws picture)
(define (draw-panda pos size)
(and
 ;;Creates arms of panda
 (draw-solid-disk (make-posn (- (posn-x pos) (* size .72)) (- (posn-y pos) (* size .72))) (* size .25) 'black)
 (draw-solid-disk (make-posn (+ (posn-x pos) (* size .72)) (- (posn-y pos) (* size .72))) (* size .25) 'black)
 (draw-solid-disk (make-posn (- (posn-x pos) (* size .72)) (+ (posn-y pos) (* size .72))) (* size .25) 'black)
 (draw-solid-disk (make-posn (+ (posn-x pos) (* size .72)) (+ (posn-y pos) (* size .72))) (* size .25) 'black)
 ;;Creates body of panda
 (draw-solid-disk pos size 'white)
 (draw-circle pos size 'black)
 ;;Creates ears
 (draw-solid-disk (make-posn (- (posn-x pos) (* size .375)) (- (posn-y pos) (* size 1.575))) (* size .25) 'black)
 (draw-solid-disk (make-posn (+ (posn-x pos) (* size .375)) (- (posn-y pos) (* size 1.575))) (* size .25) 'black)
 ;;Creates Head and covers portion of ears
 (draw-solid-disk (make-posn (posn-x pos) (- (posn-y pos) (* size 1.2))) (* size .5) 'white)
 ;;Creates black eye circles and white eyes
 (draw-solid-disk (make-posn (- (posn-x pos) (* size .25)) (- (posn-y pos) (* size 1.45))) (/ size 8) 'black)
 (draw-solid-disk (make-posn (+ (posn-x pos) (* size .25)) (- (posn-y pos) (* size 1.45))) (/ size 8) 'black)
 (draw-solid-disk (make-posn (- (posn-x pos) (* size .175)) (- (posn-y pos) (* size 1.415))) (/ size 16) 'white)
 (draw-solid-disk (make-posn (+ (posn-x pos) (* size .175)) (- (posn-y pos) (* size 1.415))) (/ size 16) 'white)
 ;;Creates Nose
 (draw-solid-rect (make-posn (- (posn-x pos) (* size .125)) (- (posn-y pos) (* size 1.2))) (* size .25) (* size .25) 'black)
 (draw-solid-disk (make-posn (- (posn-x pos) (* size .375)) (- (posn-y pos) (* size .95))) (* size .375) 'white)
 (draw-solid-disk (make-posn (+ (posn-x pos) (* size .375)) (- (posn-y pos) (* size .95))) (* size .375) 'white)
 ;;Creates Mouth
 (draw-solid-line
  (make-posn (- (posn-x pos) (* size .125)) (- (posn-y pos) (* size .95)))
  (make-posn (+ (posn-x pos) (* size .125)) (- (posn-y pos) (* size .95)))
  'black)
 ;;Outlines face
 (draw-circle (make-posn (posn-x pos) (- (posn-y pos) (* size 1.2))) (* size .5) 'black)))


;; FUNCTION #6

;;This function will draw a tank.
;;First open up your canvas by typing (start "x" "y") where x and y are the dimensions of the canvas.  I recommend 500 and 500.
;;Change the size (radius of the wheels) to increase or decrease the size of the tank.  THE SIZE MUST BE A MULTIPLE OF 20, OTHERWISE IT WILL NOT WORK!!!!!!
;;The position that you put in for the posn is the center of the middle wheel.
;;The function is (draw-tank (make-posn "some position") size color1 color2 color3)
;;Example:  (draw-tank (make-posn 300 400 40 'dimgray 'darkolivegreen 'slategray)


(define (draw-tank position size color1 color2 color3)
  (and
   ;;draw the bottom tread
   (draw-solid-rect (make-posn (- (posn-x position) (* 3 size)) 
      (posn-y position)) (* 6 size) size color2)
   ;;draw the wheels
   (draw-solid-disk position size color3)
   (draw-solid-disk (make-posn (+ (posn-x position) (* 2 size)) 
      (posn-y position)) size color3)
   (draw-solid-disk (make-posn (- (posn-x position) (* 2 size)) 
      (posn-y position)) size color3)
   ;;draw the top tread
   (draw-solid-rect (make-posn (- (posn-x position) (* 3 size))
      (- (posn-y position) (* 1.5 size))) (* 6 size) (* 0.65 size) 
	color2)
   ;;draw the left side of the tread
   (draw-solid-rect (make-posn (- (posn-x position) (* 3.25 size))
      (- (posn-y position) (* 1.5 size))) (* 0.25 size) (* size 2.5)
	color2)
   ;;draw the right side of the tread
   (draw-solid-rect (make-posn (+ (posn-x position) (* 3 size))
      (- (posn-y position) (* 1.5 size))) (* 0.25 size) (* 2.5 size)
	color2)
   ;;draw the lower body of the tank
   (draw-solid-rect (make-posn (- (posn-x position) (* 2.5 size))
      (- (posn-y position) (* 3.5 size))) (* 5 size) (* 2 size) 
	color1)
   ;;draw the barrel of the cannon
   (draw-solid-rect (make-posn (- (posn-x position) (* 6.5 size))
      (- (posn-y position) (* 3 size))) (* 4 size) (* 0.5 size)
	color2)
   ;;draw the end of the cannon
   (draw-solid-rect (make-posn (- (posn-x position) (* 6.5 size))
      (- (posn-y position) (* 3.15 size))) size (* 0.8 size)
	color3)
   ;;draw the hatch
   (draw-solid-rect (make-posn (- (posn-x position) (* 0.75 size))
      (- (posn-y position) (* 3.85 size))) (* 1.5 size) (* 0.35 size)
	color3)
   ;;draw the tread-marks
   (draw-solid-rect (make-posn (+ (posn-x position) (* 3.5 size)) 
      (posn-y position)) (* 0.25 size) size color1)
   (draw-solid-rect (make-posn (+ (posn-x position) (* 4 size)) 
      (posn-y position)) (* 0.25 size) size color1)
   (draw-solid-rect (make-posn (+ (posn-x position) (* 4.5 size)) 
      (posn-y position)) (* 0.25 size) size color1)
   (draw-solid-rect (make-posn (+ (posn-x position) (* 3.5 size)) 
      (- (posn-y position) (* 1.25 size))) (* 0.25 size) size color1)
   (draw-solid-rect (make-posn (+ (posn-x position) (* 4 size)) 
      (- (posn-y position) (* 1.25 size))) (* 0.25 size) size color1)
   (draw-solid-rect (make-posn (+ (posn-x position) (* 4.5 size)) 
      (- (posn-y position) (* 1.25 size))) (* 0.25 size) size 
	color1)))

;; FUNCTION #7

;; draw-spider consumes a posn, a number, and 3 colors (symbols)
;;
;; (draw-spider position body-radius body-color head-color legs-color)
;;   will draw a sipder with a body centered at the x,y coordinates specified
;;   by the posn structure position, with a radius of body-radius, and of color
;;   body-color, with a head above the body of color head-color, and 8 legs
;;   proportional to the body of color legs-color.
;;
;; sample usage:
;; (draw-spider (make-posn 100 100) 30 'black 'red 'black)
;;
;; note that this requires the teachpack draw.ss and requires that the start
;; function has already been called to create a window

(define (draw-spider position body-radius body-color head-color legs-color)
  (and
   (draw-legs position (posn-x position) (posn-y position) (* body-radius 2) legs-color)
   (draw-solid-disk (make-posn (posn-x position) (- (posn-y position) body-radius))
                    (floor (* body-radius .3)) head-color)
   (draw-solid-disk position body-radius body-color)
   )
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; All functions beyond this point are helper functions for the main function ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (draw-legs position x y radius color)
  (and
   (draw-solid-line position (make-posn (- x radius) (- y radius)) color)
   (draw-left-foot (- x radius) (- y radius) radius color)
   (draw-solid-line position (make-posn (- x (floor (* radius 1.3))) (- y (floor (* radius .4)))) color)
   (draw-left-foot (- x (floor (* radius 1.3))) (- y (floor (* radius .4))) radius color)
   (draw-solid-line position (make-posn (- x (floor (* radius 1.3))) (+ y (floor (* radius .4)))) color)
   (draw-left-foot (- x (floor (* radius 1.3))) (+ y (floor (* radius .4))) radius color)
   (draw-solid-line position (make-posn (- x radius) (+ y radius)) color)
   (draw-left-foot (- x radius) (+ y radius) radius color)

   (draw-solid-line position (make-posn (+ x radius) (- y radius)) color)
   (draw-right-foot (+ x radius) (- y radius) radius color)
   (draw-solid-line position (make-posn (+ x (floor (* radius 1.3))) (- y (floor (* radius .4)))) color)
   (draw-right-foot (+ x (floor (* radius 1.3))) (- y (floor (* radius .4))) radius color)
   (draw-solid-line position (make-posn (+ x (floor (* radius 1.3))) (+ y (floor (* radius .4)))) color)
   (draw-right-foot (+ x (floor (* radius 1.3))) (+ y (floor (* radius .4))) radius color)
   (draw-solid-line position (make-posn (+ x radius) (+ y radius)) color)
   (draw-right-foot (+ x radius) (+ y radius) radius color)
   )
  )

(define (draw-left-foot x y radius color)
  (draw-solid-line (make-posn x y) (make-posn (- x (floor (* radius .1))) (+ y (floor (* radius .4)))) color))

(define (draw-right-foot x y radius color)
  (draw-solid-line (make-posn x y) (make-posn (+ x (floor (* radius .1))) (+ y (floor (* radius .4)))) color))







;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;MAIN PROGRAM;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;

(start 1500 1000)

(my-world 'lightskyblue 'saddlebrown 'green 'goldenrod)

(draw-sun 100 100 50 'yellow 'orange)

(drawShape (make-posn 1150 675) 125 2 0 'black 'red) 

(draw-cloud (make-posn 100 75) 20 'gainsboro 'gray)

(drawStar (make-posn 650  60) 25 'yellow)
(drawStar (make-posn 750  25) 25 'yellow)
(drawStar (make-posn 1000 50) 25 'yellow)
(drawStar (make-posn  900 75) 25 'yellow)
(drawStar (make-posn 1100 100) 25 'yellow)
(drawStar (make-posn 1200 30) 25 'yellow)

(draw-panda (make-posn 1150 675) 16) 
(draw-panda (make-posn 1100 725) 32)

(draw-panda (make-posn 900 750) 48)
(draw-tank (make-posn 900 800) 20 'dimgray 'darkolivegreen  'slategray)

(draw-panda (make-posn 1000 850) 48)
(draw-tank  (make-posn 1000 900) 20 'dimgray 'darkolivegreen  'slategray)

(draw-panda (make-posn 800 850) 48)
(draw-tank  (make-posn 800 900) 20 'dimgray 'darkolivegreen  'slategray)

(draw-spider (make-posn 300 700) 100 'black 'red 'black)