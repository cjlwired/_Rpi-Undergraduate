;;Carlos Lazo
;;9-9-04
;;Problem Solving in Computer Science Quiz #1

;;Contract: feet->meter: number -> number

;;Purpose: to convert a number of feet entered into meters

;;Example: (feet->meter 1) should produce 0.3048 meters

;;Definition:

(define (feet->meter x)
  (* x .3048))

;;Tests:
(feet->meter 1)
;;expected value
.3048
(feet->meter 3280.8)
;;expected value
999.98784

;;;;;;;;;;;;;;;;;;;;;;;;

;;Contract: meter->feet: number -> number

;;Purpose: to convert a number of meters entered into feet

;;Example: (meter->feet 1000) should produce 3280.73 feet

;;Definition:

(define (meter->feet x)
  (/ x .3048))

;;Tests:
(meter->feet 1000)
;;expected value
3280.8398950131233595800524934383
(meter->feet 1.0)
;;expected value
3.2808398950131233595800524934383

;;;;;;;;;;;;;;;;;;;;;;;;

;;Contract: check: number -> boolean

;;Purpose: to ensure that the original number before being 
;;         changed by meter->feet is equivalent to that after using  
;;         feet->meter

;;Example: (check 1) should produce true

;;Definition:

(define (check x)
  {= x (meter->feet(feet->meter x))})

;;Tests:
(check 1)
;;expected value
true
(check 12.345)
;;expected value
true

;;;;;;;;;;;;;;;;;;;;;;;;

;;Contract: assign_letter_grade: number -> symbol

;;Purpose: to input an integer grade and to output the
;;         corresponding letter grade

;;Example: (assign_letter_grade 95) should produce 'A
;;         (assign_letter_grade 85) should produce 'B-

;;Definition:

(define (assign_letter_grade x)
  (cond
    [(> x 90) 'A]
    [(> x 80)
     (cond
       [(= 0 (modulo x 2)) 'B+]
       [else 'B-]
      )]
    [(>= x 65)
     (cond
       [(= 0 (modulo x 5)) 'A]
       [else 'C]
       )]
    [else 'F]))

;;Tests
(assign_letter_grade 91)
;;should produce
'A
(assign_letter_grade 90)
;;should produce
'B+
(assign_letter_grade 85)
;;should produce
'B-
(assign_letter_grade 76)
;;should produce
'C
(assign_letter_grade 75)
;;should produce
'A
(assign_letter_grade 64)
;;should produce
'F