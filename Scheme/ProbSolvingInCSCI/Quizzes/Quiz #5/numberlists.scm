;; Carlos Lazo
;; 10-7-04
;; Quiz #5

;; Function : generate_numbers
;; Contract : int int int -> list
;; Purpose  : creates a list of integers based on three parameters, using successive #'s from the 'start' to the 'end' in successive 'intervals'
;; Example  : (generate_numbers 0 5 1) =>
;;            Should produce : (cons 0 (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 empty))))))

(define (generate_numbers start end interval)
 (cond
   [(<= start end)
    (cond
      [ (> (+ start interval) end) (cons start empty)]
      [else
       (cons start (generate_numbers (+ start interval) end interval))])]
   [(>= start end)
    (cond
      [ (< (- start interval) end) (cons start empty)]
      [else
       (cons start (generate_numbers (- start interval) end interval))])]
   [else empty]))

"*******************************"
"*Testing out generate_numbers:*"
"*******************************"

;; Test  1
(generate_numbers 0 5 1)
;; Should print:
(cons 0(cons 1(cons 2(cons 3(cons 4(cons 5 empty))))))

;; Test 2
(generate_numbers 10 5 1)
;; Should print:
(cons 10 (cons 9 (cons 8 (cons 7 (cons 6 (cons 5 empty))))))

;; Test 3
(generate_numbers 100 1000 222)
;; Should print:
(cons 100 (cons 322 (cons 544 (cons 766 (cons 988 empty)))))

;; Test 4
(generate_numbers 1 10 25)
;; Should print:
(cons 1 empty)

;; Function : merge-sorted-lons
;; Contract : list list -> list
;; Purpose  : creates and returns a list which is the merge of the two lists that are sent to the function
;; Example  : merge-sorted-lons even odd) =>
;;            Should produce : (cons 0 (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 (cons 6 (cons 7 (cons 8 (cons 9 empty))))))))))

(define even   (list 0 2 4 6 8))
(define odd    (list 1 3 5 7 9))
(define spread (list 1 100 200 300))

(define (merge-sorted-lons listOne listTwo)
  (cond
    [(and (empty? listOne) (empty? listTwo)) empty]
    
    [(empty? listOne) 
     (cons (first listTwo) (merge-sorted-lons listOne (rest listTwo)))]
    
    [(empty? listTwo) 
     (cons (first listOne) (merge-sorted-lons (rest listOne) listTwo))]
    
    [ (<= (first listOne) (first listTwo)) (cons (first listOne) (merge-sorted-lons (rest listOne) listTwo))]
    [ (>= (first listOne) (first listTwo)) (cons (first listTwo) (merge-sorted-lons (rest listTwo) listOne))]
    [ else empty]))

"********************************"
"*Testing out merge-sorted-lons:*"
"*******************************"

;; Test 1
(merge-sorted-lons even odd)
;; Should print:
(cons 0 (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 (cons 6 (cons 7 (cons 8 (cons 9 empty))))))))))

;; Test 2
(merge-sorted-lons odd even)
;; Should print:
(cons 0 (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 (cons 6 (cons 7 (cons 8 (cons 9 empty))))))))))

;; Test 3
(merge-sorted-lons even empty)
;; Should print:
(cons 0 (cons 2 (cons 4 (cons 6 (cons 8 empty)))))

;; Test 4
(merge-sorted-lons odd spread)
;; Should print:
(cons 1 (cons 1 (cons 3 (cons 5 (cons 7 (cons 9 (cons 100 (cons 200 (cons 300 empty)))))))))


;; NOTE : To use error function, type in the followng for example:
;;        [else (error 'add "Numbers Expected")]
;;
;;      This will be printed:
;;             add : Numbers expected


;; Function : interp
;; Contract : list -> integer
;; Purpose  : takes a list and interprets it into an integer utilizing the definitions stated within the function
;; Example  : (interp (list 12 'plus 13))
;;            Should produce : 25

(define (interp list)
  (cond
    ;; Checks to see if the first element in the list is a list - if it is, evaluate the first element using a recursive call and add it to the list
    [(list? (first list)) (interp (cons (interp (first list)) (cons (first(rest list)) (cons (first(rest(rest list))) empty))))]
    ;; Checks to see if the third element in the list is a list - if it is, evaualte the  last element using a recursive call and add it to the list
    [(list? (first(rest(rest list)))) (interp (cons (first list) (cons (first(rest list)) (cons (interp (first(rest(rest list)))) empty))))]
    [(symbol=? 'plus  (first (rest list)))  (+ (first list) (first(rest(rest list))))]
    [(symbol=? 'minus (first (rest list)))  (- (first list) (first(rest(rest list))))]
    [(symbol=? 'times (first (rest list)))  (* (first list) (first(rest(rest list))))]
    [(symbol=? 'div   (first (rest list)))  (/ (first list) (first(rest(rest list))))]
    [else (error 'interp "Operation that was sent to interp is not valid")]))

"*********************"
"*Testing out interp:*"
"*********************"

;; Test 1
(interp (list 12 'plus 13))
;; Should print:
25
;; Test 2
(interp (list 85 'div 5))
;; Should print:
17

;; Test 3
(interp (list 3 'times 2)) 
;; Should print:
6

;; Test 4
;;(interp (list 33 'blah 33)) 
;; Should print: Invalid

;; Test 5
(interp (list 12 'plus (list 14 'minus 3))) 
;; Should print:
23

;; Test 6
(interp
  (list
     (list 3 'times 4)
     'plus
     (list 10 'div 5)))
;; Should print:
14