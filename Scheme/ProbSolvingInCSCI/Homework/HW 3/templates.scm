;; Carlos Lazo
;; 10-10-04
;; Problem Solving in Computer Science
;; Homework #3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Template: Counting Function ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This template describes scheme functions that utilize a counter, normally an integer value, to iterate through a function performing the
;; desired action till the counter is exhausted in some way. The majority of counting functions use recursion and the counter as the base 
;; case in a cond statement to "kick out" of the function.

;; The functions that match this template can consume many different variables and normally an integer counter. For the majority of times, the 
;; function will be called over again until the counter reaches a certain value recursively, where it will then cease to call itself again.

;; General structure of the function definition:

;; (define (func <variables> counter)
;;     (cond
;;        [<counter check statement>]
;;        .... Any other desired actions
;;        [<recursive call of func normally changing the value of counter making it near the base case check statement>]))

;; Example 1: add-yourself

;; function add-yourself number number => number

;; (add-yourself num counter) take a number and a counter. This functions add the number to itself "counter" times. The base case
;; will stop when the counter becomes less than 0. This is another way of writing the multiplication operator using addition
;; and recursion.

;; sample usage: (add-myself 5 9)

(define (add-myself num counter)
  (cond
    [(< counter 1) 0]
    [else (+ num (add-myself num (- counter 1)))]))

(add-myself 5 9)
;; Should produce:
45

(add-myself 10 6)
;; Should produce:
60

(add-myself 9 9)
;; Should produce:
81

;; Example 2: muliply-myself

;; function myself-yourself number number => number

;; (myself-yourself num counter) take a number and a counter. This functions mutliplies the number to itself "counter" times. The base case
;; will stop when the counter becomes less than 0. This is another way of writing a function where number is raised to the "counter" power.

;; sample usage: (mutliply-myself 5 3)

(define (multiply-myself num counter)
  (cond
    [(< counter 1) 1]
    [else (* num (multiply-myself num (- counter 1)))]))

(multiply-myself 5 3)
;; Should produce:
125

(multiply-myself 4 4)
;; Should produce:
256

(multiply-myself 9 2)
;; Should produce:
81

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Template: Modifying a Structure ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This template describes scheme functions that modify a structure. Normally, these functions change one of the parameters or variables
;; of the structure and return the new structure.  

;; The functions that match this template normally consume a structure and a value used to change the structure in some way. This is done by
;; creating a new structure with the same values as the original structure but with one of the values changed. The majority of modifying
;; functions are called once; some, like drawing functions for example, are called recursively.

;; General structure of the function definition:

;; (define (func <structure> value)
;;     (<creating new structure, with a parameter as a new value>))

;; Example 1: grow-radius

;; function grow-radius structure number => structure

;; (grow-radius circle radius) takes a circle structure and an integer. This function creates a new circle now with the old radius plus the 
;; new integer sent to the function. Of course, the structure 'circle' must be defined before being able to implement the function.

;; sample usage: (grow-radius (make-circle (make-posn 100 100) 10 'blue) 40)

(define-struct circle (center radius color))

(define (grow-radius c radius)
  (make-circle (circle-center c) (+ (circle-radius c) radius) (circle-color c)))

(grow-radius (make-circle (make-posn 100 100) 10 'blue) 40)
;; Should produce:
(make-circle (make-posn 100 100) 50 'blue)

(grow-radius (make-circle (make-posn 250 250) 50 'red) 500)
;; Should produce:
(make-circle (make-posn 250 250) 550 'red)

(grow-radius (make-circle (make-posn 23 25) 24 'yellow) 89)
;; Should produce:
(make-circle (make-posn 23 25) 113 'yellow)

;; Example 2: multiply-square

;; function double-square structure number => structure

;; (mutiply-square square number) takes a square structure and multiplies it's side by the number, increasing its size (both lenght and width ).
;; Of course, the structure square must be made before implementing the function.

;; sample usage: (multiply-square (make-square (make-posn 100 100) 10) 10)

(define-struct square (center side color))

(define (multiply-square s multiplier)
  (make-square (square-center s) (* (square-side s) multiplier) (square-color s)))


(multiply-square (make-square (make-posn 150 150) 50 'blue) 2)
;; Should produce:
(make-square (make-posn 150 150) 100 'blue)

(multiply-square (make-square (make-posn 500 500) 100 'red) 5)
;; Should proudce:
(make-square (make-posn 500 500) 500 'red)

(multiply-square (make-square (make-posn 301 301) 67 'green) 8)
;; Should produce:
(make-square (make-posn 301 301) 536 'green)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Template: Removing an Item from a List ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This template describes scheme functions that remove items from a list. These functions work as the maker defines them. For example, one can
;; choose to remove the first or last element of the list, of they can remove items based upon values.

;; The functions that match this template consume a list and possibly some other variable, such as an integer which is used to remove certain items 
;; from the list. These functions can also be recurisve if the desire is to check each element for validity according to the function definition. For
;; recursion to happen, one must use a cond statement with a base case checking if the list is empty.

;; General structure of the function definition:

;; (define (func list <possibly some value>)
;;     (cond
;;       [<base case> - normally returns empty or part of the list]
;;       [<check statement of some sort> append item to list, recursive call to func]
;;       [else <do not append item of list, recursive call to func>]))
;; * In the case of just removing the first or last element, recursive calls are not needed.

;; Example 1 : remove-first

;; function remove-first list => list

;; remove-first simply removes the first element of the list that it is sent. It makes sure that if the lest is empty, it just returns 
;; empty, to prevent an error.

;; sample usage: (remove-first (cons 1 (cons 2 (cons 3 empty))))

(define (remove-first list)
  (cond
    [(empty? list) empty]
    [else (rest list)]))

(remove-first (cons 1 (cons 2(cons 3 empty))))
;; Should produce:
(cons 2 (cons 3 empty))

(remove-first (cons 'a (cons 'b (cons 'c (cons 'd (cons 'e (cons 'f empty)))))))
;; Should produce:
(cons 'b (cons 'c (cons 'd (cons 'e (cons 'f empty)))))

;; Example 2 : remove-val

;; function remove-val list number => list

;; remove-val takes in a list and removes all instances of number found within it, returning the new list. It uses recursion with a check statement
;; as well, to ensure that no error is made.

;; sampe usage: (remove-val (cons 1(cons 2(cons 3(cons 1 empty)))) 1)

(define (remove-val list num)
  (cond
    [(empty? list) empty]
    [(= (first list) num) (remove-val (rest list) num)]
    [else (cons (first list) (remove-val (rest list) num))]))

(remove-val (cons 1(cons 2(cons 3(cons 1 empty)))) 1)
;; Should produce:
(cons 2 (cons 3 empty))

(remove-val (cons -1 (cons 4 (cons -1 (cons -1 (cons 5 (cons 100 (cons 24 (cons -1 (cons 99 empty))))))))) -1)
;; Should produce:
(cons 4 (cons 5 (cons 100 (cons 24 (cons 99 empty)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Template: Adding an Item from to a List ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This template describes scheme functions that add items to a list. These functions work as the maker defines them. For example, one can
;; choose to add an element infront of or at the end of a list, or they can add elements based on position.

;; The functions that match this template consume a list and possibly some other variable, such as an integer which can be used to append items to the 
;; list based on position. These functions can also be recurisve if the desire is to iterate through to add an element. For recursion to happen with 
;; addition to a list, one must keep track of the position in the list and then proceed to add the element.

;; General structure of the function definition:

;; (define (func list <possibly some value>)
;;     (cond
;;       [<base case> - if iteration through list is in the right position, place new element here and append rest of the list]
;;       [else <recur back and increment counter]))
;; * In the case simply adding an element, adding an element in the front will not require recursive calls, where adding an element to the end will.

;; Example 1: add-end

;; function add-end list element => list

;; add-end takes a list and an element and appends the element to the end of the list using recursion

;; sample usage: (add-end (cons 1 (cons 2 (cons 3 empty))) 4)

(define (add-end list element)
  (cond
   [ (empty? list) (cons element list) ]
   [ else 
	 (cons (first list) (add-end (rest list) element))]))

(add-end (cons 1 (cons 2 (cons 3 empty))) 4)
;; Should produce:
(cons 1 (cons 2 (cons 3 (cons 4 empty))))

(add-end (cons 'P (cons 'S (cons 'i (cons 'C empty)))) 'S)
;; Should produce:
(cons 'P (cons 'S (cons 'i (cons 'C (cons 'S empty)))))

;; Example 2: add-position

;; function add-position list element position counter => list

;; add-position takes a list and a element, and appends the element to the list at position. The counter will be used
;; and incremented after each recursive call to help keep track of the place in the list.

(define (add-position list element position counter)
  (cond
   [(empty? list) empty]
   [(= counter position) (cons element (cons (first list) (rest list)))]
   [else (cons (first list) (add-position (rest list) element position (+ counter 1)))]))

(add-position (cons 1 (cons 2 (cons 4 empty))) 3 3 1)
;; Should produce:
(cons 1 (cons 2 (cons 3 (cons 4 empty))))

(add-position (cons 'a (cons 'b (cons 'c (cons 'd (cons 'e (cons 'g (cons 'h empty))))))) 'f 6 1)
;; Should produce:
(cons 'a (cons 'b (cons 'c (cons 'd (cons 'e (cons 'f (cons 'g (cons 'h empty))))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Template: Processing a List in Order ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This template describes scheme functions that process lists in order. These functions can be used to print values, perform mathematical operations, etc.

;; The functions that match this template consume a list, and iterate throught it using recursion to accomplish the desired task. A base case is always
;; necessary when dealing with recursion to prevent errors.

;; General structure of the function definition:

;; (define (func list)
;;     (cond
;;       [<base case> - will eventually stop the function, normally done when the list is empty
;;       [else (cons <perform operation> <recursive call back to func>]))

;; Example 1: add-list-elem

;; function add-list-elem list => num

;; add-list-elem takes a list and adds up all of the values within it, returning an integer value

;; sample usage: (add-list-elem (cons 1 (cons 2 (cons 3 (cons 4 empty))))

(define (add-list-elem list)
  (cond
   [(empty? list) 0]
   [else (+ (first list) (add-list-elem (rest list)))]))

(add-list-elem (cons 1 (cons 2 (cons 3 (cons 4 empty)))))
;; Should produce:
10

(add-list-elem (cons 100 (cons 200 (cons 300 (cons 400 (cons 500 empty))))))
;; Should produce:
1500

;; Example 2: count-element

;; function count-element list element => num

;; count-element takes a list and an element and returns the number of instances that the element was found in the list

;; sample usage: (count-element (cons 1 (cons 2 (cons 2 (cons 3 (cons 2 empty))))) 2)

(define (count-element list elem)
  (cond
    [(empty? list) 0]
    [(= (first list) elem) (+ 1 (count-element (rest list) elem))]
    [else (+ 0 (count-element (rest list) elem))]))

(count-element (cons 1 (cons 2 (cons 2 (cons 3 (cons 2 empty))))) 2)
;; Should produce:
3

(count-element (cons 501 (cons 909 (cons 909 (cons 123 (cons 909 (cons 909 (cons 909 (cons 110 (cons 909 empty))))))))) 909)
;; Should produce:
6

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Template: Processing a List in Reverse Order ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This template describes functions that process lists in reverse order. Normally, a helper function to reverse the list is invoked first,
;; and then the list is processed in some way, shape, or form.

;; The functions that match this template normally take a list and reverse it at first, and then it is processed according to the function
;; definition. Recursion is used along with a base case to prevent errors.

;; General structure of the function definition:

;; (define (func list)
;;  (cond
;;   [<base case, mostly to check if the list is empty>]
;;   [<recursive call using cons statements to create the new reversed list>]))

;; Example 1: reverse-list

;; function reverse-list list => list

;; reverse-list takes a list and utilizes a temporary helper function along with an empty list to reverse the function

;; sample usage: (reverse-list (cons 1 (cons 2 (cons 3 (cons 4 empty)))))

(define (reverse-list-helper list1 list2)
  (cond
    [(empty? list1) list2]
    [else (reverse-list-helper (rest list1) (cons (first list1) list2))]))

(define (reverse-list list1)
  (reverse-list-helper list1 empty))

(reverse-list (cons 1 (cons 2 (cons 3 (cons 4 empty)))))
;; Should produce:
(cons 4 (cons 3 (cons 2 (cons 1 empty))))

(reverse-list (cons 'g (cons 'f (cons 'e (cons 'd (cons 'c (cons 'b (cons 'a empty))))))))
;; Should produce:
(cons 'a (cons 'b (cons 'c (cons 'd (cons 'e (cons 'f (cons 'g empty)))))))

;; Example 2 : add-to-reverse

;; function add-to-reverse list element => list

;; add-to-reverse first appends the element to the beginning of the list, then it proceeds to reverse the list, now making it 
;; the last element in the reversed list

;; sample-usage (add-to-reverse list element)

(define (add-to-reverse list element)
  (reverse-list (cons element list)))

(add-to-reverse (cons 1 (cons 2 (cons 3 (cons 4 empty)))) 0)
;; Should produce:
(cons 4 (cons 3 (cons 2 (cons 1 (cons 0 empty)))))

(add-to-reverse (cons 100 (cons 200 (cons 345 (cons 999 empty)))) 1)
;; Should produce:
(cons 999 (cons 345 (cons 200 (cons 100 (cons 1 empty)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Template: Processing a List of Structures ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; This template describes functions that process lists of structures. This is normally done when one wants to change many structures at once,
;; or in another example, create an animation.

;; The functions that process structures take in a list and normally some sort of variable/value to change the structures within the list. 
;; Again, recursion is key when working with lists.

;; General structure for the function definition:

;; (define (func list <variables>)
;;  (cond
;;   [<check statement to exit the recursion>]
;;   [<change value and recur back to func]))

;; Example 1: add-radius

;; function add-radius list num => list

;; add-radius adds the num to the radius of all circles that are in the list

(define (add-radius list num)
  (cond
   [(empty? list) empty]
   [else (cons (make-circle (circle-center (first list)) (+ (circle-radius (first list)) num) (circle-color (first list))) 
              (add-radius (rest list) num))]))

(add-radius (cons (make-circle (make-posn 150 150) 100 'blue) (cons (make-circle (make-posn 200 200) 50 'red) empty)) 50)
;; Should produce:
(cons (make-circle (make-posn 150 150) 150 'blue) (cons (make-circle (make-posn 200 200) 100 'red) empty))

;; Example 2: multiply-side

;; function multiply-side list num => list

;; multiply-side mutiplies the sides of each of the squares in the list

(define (multiply-side list num)
  (cond
   [(empty? list) empty]
   [else (cons (make-square (square-center (first list)) (* (square-side (first list)) num) (square-color (first list))) 
              (multiply-side (rest list) num))]))

(multiply-side (cons (make-square (make-posn 150 150) 100 'blue) (cons (make-square (make-posn 200 200) 50 'red) empty)) 2)
;; Should produce:
(cons (make-square (make-posn 150 150) 200 'blue) (cons (make-square (make-posn 200 200) 100 'red) empty))




