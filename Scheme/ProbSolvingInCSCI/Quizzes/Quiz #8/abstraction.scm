;; Carlos Lazo
;; 10-28-04
;; Quiz #8 - Abstraction

;;;;;;;;;;;;
;; PART 1 ;;
;;;;;;;;;;;;

;; compare-arbitrary-elems is a function that takes two elements from a list that is being utilized by quicksort.
;; Using a lot of conditional statements specified by the quiz instructions, it checks to see what types of elements
;; the variables sent to the function are and accordingly send back the appropriate comparison.

(define (compare-arbitrary-elems elem1 elem2)
  (cond
    [(and (number? elem1) (number? elem2)) (< elem1 elem2)]
    [(and (string? elem1) (string? elem2)) (string<? elem1 elem2)]
    [(and (symbol? elem1) (symbol? elem2)) (string<? (symbol->string elem1) (symbol->string elem2))]
    [(and (number? elem1) (or (string? elem2) (symbol? elem2))) true]  
    [(and (number? elem2) (or (string? elem1) (symbol? elem1))) false]  
    [(and (string? elem1) (symbol? elem2)) true]
    [(and (string? elem2) (symbol? elem1)) false]
    [else true]
    )
  )

(define example '(1000 22 Fred "Hello World" 33 Sally "PSICS" 1024))

"After being sorted, example which looks like:"
example
"Should look like: "
(list 22 33 1000 1024 "Hello World" "PSICS" 'Fred 'Sally)

"My run: "
(quicksort example compare-arbitrary-elems)

;;;;;;;;;;;;
;; PART 2 ;;
;;;;;;;;;;;;

;; usort is a function that takes any type of list and sorts it accordingly. Since all of the necessary comparisons were
;; already contained within the function I had defined in Part 1, I just decided to use it again for simplicity.

(define (usort list)
  (quicksort list compare-arbitrary-elems))

"Test 1"
'(1 8 2 9 33 26 3 22 7 45 100)
"After being sorted should look like:"
(list 1 2 3 7 8 9 22 26 33 45 100)
(usort '(1 8 2 9 33 26 3 22 7 45 100))

"Test 2"
'(seven two one three eight twelve)
"After being sorted should look like:"
(list 'eight 'one 'seven 'three 'twelve 'two)
(usort '(seven two one three eight twelve))

"Test 3"
'("Hello" "World" "Scheme" "is" "fun")
"After being sorted should look like:"
(list "Hello" "Scheme" "World" "fun" "is")
(usort '("Hello" "World" "Scheme" "is" "fun"))

;;;;;;;;;;;;
;; PART 3 ;;
;;;;;;;;;;;;

;; remove-duplicates, defined utilizing a local scope, was generalized by passing a relational operator (relop)
;; to it. Within the helper function, which creates a list from the rest of the list at that moment void of all
;; instances of x, I changed the symbol=? and the = to relop. I also had to make sure to make sure to pass the
;; relop recursively.

(define (remove-duplicates alos relop)
  (local
   ((define (remove-from-list alos x)
        (cond
           [(empty? alos) empty]
           [(relop x (first alos))
                (remove-from-list (rest alos) x)]
           [else
                (cons (first alos) (remove-from-list (rest
		alos) x))])))
  (cond
   [(empty? alos) empty]
   [else
        (cons (first alos)
                  (remove-duplicates
                   (remove-from-list (rest alos) (first
		   alos)) relop))])))

"Test 1"
'(Sally Fred George Sally Sam Fred Sally Sally)
"After having duplicates removed should look like:"
(list 'Sally 'Fred 'George 'Sam)
(remove-duplicates '(Sally Fred George Sally Sam Fred Sally Sally) symbol=? )

"Test 2"
'(1 2 3 1 2 3 1 2 3 4 5 4 )
"After having duplicates removed should look like:"
(list 1 2 3 4 5)
(remove-duplicates '(1 2 3 1 2 3 1 2 3 4 5 4 ) = )

;;;;;;;;;;;;
;; PART 4 ;;
;;;;;;;;;;;;

;; Utilizing the same function from above, for this to work with a list of mixed elements, all that has to be
;; done is that you have to send the equal? operator to the function. This way, it will check to see if the 
;; element is equal to another one. If so, ignore it and continue

"Test 1"
'(1 Sally 2 Fred 3 George 1 2 3 Sam 4 Fred 5 Sally 2 Sally 4)
"After having duplicates removed should look like:"
(list 1 'Sally 2 'Fred 3 'George 'Sam 4 5)
(remove-duplicates '(1 Sally 2 Fred 3 George 1 2 3 Sam 4 Fred 5 Sally 2 Sally 4) equal?)

;; NOTE : Thanks Dave for this giving us this fairly simple quiz. I thoroughly enjoyed it, and I was in need of a break. 