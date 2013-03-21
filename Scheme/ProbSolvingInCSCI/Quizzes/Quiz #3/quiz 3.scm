;; Carlos Lazo
;; 9-23-04
;; Quiz #3


;; drawing functions that eliminate the "it's not an integer" hassle
;; these all take the floor of all numbers used for drawing
;;   before calling the corresponding draw- function

(define (idraw-circle center radius color)
  (draw-circle
   (make-posn
    (floor (posn-x center))
    (floor (posn-y center)))
   (floor radius)
   color))

(define (iclear-solid-disk center radius)
  (clear-solid-disk
   (make-posn
    (floor (posn-x center))
    (floor (posn-y center)))
   (floor radius)))

(define (idraw-solid-disk center radius color)
  (draw-solid-disk
   (make-posn
    (floor (posn-x center))
    (floor (posn-y center)))
   (floor radius)
   color))

(define (idraw-solid-rect topleft width height color)
  (draw-solid-rect
   (make-posn (floor (posn-x topleft))
			  (floor (posn-y topleft)))
   (floor width)
   (floor height)
   color))

(define (iclear-solid-rect topleft width height)
  (clear-solid-rect
   (make-posn (floor (posn-x topleft))
			  (floor (posn-y topleft)))
   (floor width)
   (floor height)))

;===============================================================
; draw one eye with center and size specified.
;  an eye is a white circle with black border and
;   black pupil.
;;   direction can be 'left, 'center, or 'right
;;   and determines where the pupil is drawn.
;;   center is looking straight ahead, left looks to
;;    the left, etc.
(define (draw-eye center size direction)
  (and
   (idraw-solid-disk center (floor size) 'white)
   (idraw-circle center (floor size) 'black)
   (cond
     [(symbol=? direction 'left) 
      (idraw-solid-disk 
       (make-posn
        (- (posn-x center) (* size 0.75))
        (posn-y center))
        (* size 0.30) 'black)]

     [(symbol=? direction 'right) 
      (idraw-solid-disk 
       (make-posn
        (+ (posn-x center) (* size 0.75))
        (posn-y center))
	   (* size 0.30) 'black)]
     
     ;; Added up direction for movement of eyes
     
     [(symbol=? direction 'up) 
      (idraw-solid-disk 
       (make-posn
        (posn-x center)
        (- (posn-y center) (* size 0.75)))
	   (* size 0.30) 'black)]
     
     ;; Added down direction for movement of eyes
     
     [(symbol=? direction 'down) 
      (idraw-solid-disk 
       (make-posn
        (posn-x center)
        (+ (posn-y center) (* size 0.75)))
	   (* size 0.30) 'black)]
     
     
     
     
     [else
      (idraw-solid-disk 
	   center
        (* size 0.30) 'black)]
	 )))
     

;;draw-kyle needs a posn, number and symbol
;;  posn is the center of kyle's head.
;;  number is the radius of kyle's head.
;;  symbol determines where kyle is looking:
;;    'left - he is looking to our left.
;;    'right - he is looking to our right.
;;    'center - he is looking at us.
;;    
;; sample: (draw-kyle (make-posn 100 100) 50 'center)
;; 
(define (draw-kyle center size look)
  (and
   ;;create face
   (idraw-solid-disk center size 'blanchedalmond)
   ;;create hat
   (idraw-solid-rect 
	(make-posn 
	 (- (posn-x center) (* size .8))
	 (- (posn-y center) (* size 1.2)))
	 (* size 1.6) 
	 (* size .6) 
	 'darkblue)

   (idraw-solid-rect 
	(make-posn 
	 (- (posn-x center) (* size .6)) 
	 (- (posn-y center) (* size .8))) 
	(* size 1.2) 
	(* size .2) 
	'darkred)
   ;; draw eyes
   (draw-eye 
	(make-posn 
	 (- (posn-x center) (* size .25))
	 (- (posn-y center) (* size .25)))
	 (* size .25) look)

   (draw-eye 
	(make-posn 
	 (+ (posn-x center) (* size .25))
	 (- (posn-y center) (* size .25)))
	 (* size .25) look)
   ;; draw mouth
   (draw-solid-disk 
	(make-posn 
	 (posn-x center) 
	 (+ (posn-y center) (* size .5))) 
	(* size 0.1) 
	'black)
))


;;clear-kyle needs a posn and a number
;;  posn is the center of kyle's head.
;;  number is the radius of kyle's head.

;; sample: (clear-kyle (make-posn 100 100) 50 )
;; 
(define (clear-kyle center size)
  (and
   ;;create face
   (iclear-solid-disk center size)
   ;;create hat
   (iclear-solid-rect 
	(make-posn 
	 (- (posn-x center) (* size .8))
	 (- (posn-y center) (* size 1.2)))
	 (* size 1.6) 
	 (* size .6) 
	 )))

;;
;; YOUR CODE GOES HERE
;;


;; I decided to implement this problem as a recursive function. The control variable here is the radius that one enters. As soon as the radius
;; gets lower than 10, the recursive function will cease. Every single time it calls itself, it draws itself as a different animation with a 
;; smaller radius, given the appreance of the head shrinking. As you can see, each of the conditional statements depends on the function 'look' of
;; the picture. I decided to add at the top of the code an 'up and 'down function to the eyes so I could make four different animations with every
;; step. The delay time is up to the user, as is the decay, but it is IMPERATIVE that the decay is a multiple of 10 because the code above requires
;; integers to work. Any doubles that appear will cause an error.

(start 1000 1000)

(define (draw-recursive-kyle point radius look time decay)
  (cond
    [(<= radius 10) true]
    [(symbol=? look 'left) 
     (and
      (draw-kyle (make-posn (posn-x point) (posn-y point)) radius look)
      (sleep-for-a-while time)
      (clear-kyle point radius)
      (draw-recursive-kyle (make-posn (+ (posn-x point) 1) (posn-y point)) (- radius decay) 'up time decay))]
    [(symbol=? look 'up) 
     (and
      (draw-kyle (make-posn (posn-x point) (posn-y point)) radius look)
      (sleep-for-a-while time)
      (clear-kyle point radius)
      (draw-recursive-kyle (make-posn (+ (posn-x point) 1) (posn-y point)) (- radius decay) 'right time decay))]
    [(symbol=? look 'right) 
     (and
      (draw-kyle (make-posn (posn-x point) (posn-y point)) radius look)
      (sleep-for-a-while time)
      (clear-kyle point radius)
      (draw-recursive-kyle (make-posn (+ (posn-x point) 1) (posn-y point)) (- radius decay) 'down time decay))]
    [(symbol=? look 'down) 
     (and
      (draw-kyle (make-posn (posn-x point) (posn-y point)) radius look)
      (sleep-for-a-while time)
      (clear-kyle point radius)
      (draw-recursive-kyle (make-posn (+ (posn-x point) 1) (posn-y point)) (- radius decay) 'left time decay))]))

(draw-recursive-kyle (make-posn 500 500) 500 'up .1 10)
   

