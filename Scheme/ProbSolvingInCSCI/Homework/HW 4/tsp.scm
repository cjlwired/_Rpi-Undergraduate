;; Carlos Lazo
;; 12-9=04
;; REVISED : Homework #4
;; Traveling Salesman Problem


;; After reading over the comment that you sent me, what I did to change the program what that I used a local definition.
;; All function were added within the scope, and at the end, the cost and the minimum tour list are printed out. Now, instead of
;; having to manually change everything, all you have to do is send a list to the TSP function and it will calculate everything
;; for you. The algorithm works as it did, it's just a lot cleaner now. If you still have any questions or comments, feel free
;; to e-mail me back. -> lazoc@rpi.edu  ~ Thanks.

(define (TSP a-list)
  (local
      (
       
       (define travel-cost a-list)
       
       
       (define (get-travel-cost list index counter)
         (cond
           [(empty? list) (error' get-travel-cost "travel-cost list is returning an empty value")]
           [(= counter index) (first list)]
           [else (get-travel-cost (rest list) index (+ counter 1))]
           )
         )
       
       ;; The following code for generate-permutations has been taken from Professor Hollinger's code posted online.
       
       (define (add-element-to-lists elem lists)
         (cond 
           [(empty? lists) empty]
           [ else
             (cons 
              (cons elem (first lists))
              (add-element-to-lists elem (rest lists)))]))
       
       (define (generate-permutations alist)
         (cond
           [(empty? alist) (list empty)]
           [(empty? (rest alist)) (list alist)]
           [ else
             (use-each-element-as-start alist)]))
       
       (define (use-each-element-as-start alist)
         (use-each-element-as-start-helper empty alist))
       
       (define (use-each-element-as-start-helper done remaining)
         (cond
           [(empty? remaining) empty]
           [else
            (append
             (add-element-to-lists
              (first remaining)
              (generate-permutations
               (append done (rest remaining))))
             (use-each-element-as-start-helper
              (append done (list (first remaining)))
              (rest remaining)))]))
       
       ;; make-circular-lists takes a list of lists and appends the first value in each individual list to the end of that
       ;; list. I decided to use a local scope including the function addright, which adds the given element to the end 
       ;; of the given list. This is being used in conjunction with make-circular-lists to add the element to the end of the lists.
       
       (define (make-circular-lists list)
         (cond
           [(empty? list) empty]
           [else
            (local
                ( (define (addright elem alist)
                    (cond
                      [ (empty? alist) (cons elem alist) ]
                      [ else 
                        (cons (first alist) (addright elem (rest alist)))])))
              (cons (addright (first (first list)) (first list)) (make-circular-lists (rest list))))]
           )
         )
       
       
       
       ;; get-value is a helper function that is used to get each of the individual values within the list that it is given
       ;; within the list of costs that it will be given
       
       (define (get-value list index counter)
         (cond
           [(empty? list) (error' get-value "get-value is returning an empty value")]
           [(= counter index) (first list)]
           [else (get-value (rest list) index (+ counter 1))]
           )
         )
       
       ;; cost-between-cities is a function that is given a list-index which corresponds to that specific list in travel-costs,
       ;; and where val is the actual value that is attained from that specific list
       
       (define (cost-between-cities list-index val)
         (get-value (get-travel-cost travel-cost list-index 0) val 0))
       
       ;; sum-tour takes in the list which represents a tour and calculates using recursion the total distance
       ;; it will take to travel from city to city
       
       (define (sum-tour list list-index counter)
         (cond
           [(= counter comparisons) 0]
           [else
            (+ (cost-between-cities list-index (first (rest list))) (sum-tour (rest list) (first(rest list)) (+ counter 1)))]
           )
         )
       
       ;; sum-of-all-tours takes the list of list created above of all permutations and calculates each and every value,
       ;; storing the corresponding values in a list of integers
       
       (define (sums-of-all-tours list)
         (cond
           [(empty? list) empty]
           [else
            (cons (sum-tour (first list) (first (first list)) 0) (sums-of-all-tours (rest list)))]))
       
       ;; min-cost takes the list of costs that was generated and finds the smallest value and then returns it
       
       (define (min-cost list elem)
         (cond
           [(empty? list) elem]
           [else
            (cond
              [( < (first list) elem) (min-cost (rest list) (first list))]
              [else (min-cost (rest list) elem)])]
           )
         )
       
       ;; get-index-of-min returns the index of the smallest value in the list of integers that corresponds to the 
       ;; values of each individual tour
       
       (define (get-index-of-min list min-val counter)
         (cond
           [(empty? list) (error' get-index-of-min "returning empty")]
           [(= min-val (first list)) counter]
           [else (get-index-of-min (rest list) min-val (+ counter 1))]))
       
       ;; get-efficient-tour returns a tour that has the minimum value in the list of all tours
       
       (define (get-efficient-tour list counter index)
         (cond 
           [(empty? list) (error' get-efficient-tour "returning empty")]
           [(= counter index) (first list)]
           [else (get-efficient-tour (rest list) (+ counter 1) index)]))
       
       
       ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       ;;;;;;;;;;;;;;;;;;; DEFINITIONS ;;;;;;;;;;;;;;;;;;;;;;
       ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       
       
      ;; This value is changed based upon the number of total comparisons that will be made within the list.
       ;; The number of comparisons that will be made are equal to the number of cities in the list.
       
       (define comparisons
         (local
             ((define (find-comparisons alist counter)
                (cond
                  [(empty? alist) counter]
                  [else (find-comparisons (rest alist) (+ 1 counter))])))
           (find-comparisons travel-cost 0)))
       
       ;; travel-perms if a variable defined to hold the list of lists of all permutations possible for all elements
       ;; sent to the function
       
       (define trav-perms 
         (local
             (
              (define (make-trav-list n counter)
                (cond
                  [(= n counter) empty]
                  [else (cons counter (make-trav-list n (+ 1 counter)))]))
              
              (define trav-list (make-trav-list comparisons 0)))
              
         (generate-permutations trav-list)))
       
       ;; circ-perms is defined as a variable that now contains the new circular lists that will in the end be used
       ;; to calculate costs
       
       (define circ-perms (make-circular-lists trav-perms))
       
       ;; Defining variable called all-sums which stores all of the sums from the tours
       
       (define all-sums (sums-of-all-tours circ-perms))
       
       ;; Defining variable callbe first-sum which stores first element in the sum list for future use
       
       (define first-sum (first all-sums))
       
       ;; Defining a variable that stores the minimum value of all the tours
       
       (define min-tour-cost (min-cost all-sums first-sum))
       
       ;; Defining variable that will find the first place in the integer list that a minimum value is found
       
       (define min-counter (get-index-of-min all-sums min-tour-cost 0)) 
       
       ;; Defining variable that will hold the list of one of the tours that costs the least. This works due to the fact
       ;; that each of individual lists of permutations is in parallel to the integer lists of their corresponding values.
       
       (define min-tour (get-efficient-tour circ-perms 0 min-counter))
       
       (define min-cost-list 
         (local
             ((define (make-list n)
                (cons n empty)))
           (make-list min-tour-cost))))
                   
    (append min-cost-list min-tour)))

;; 4 city problem
(define cities4 '(
(  0 10 20  3)
( 10  0  5  8)
( 20  5  0  1)
(  3  8  1  0)))
  

;; 5 city problem
(define cities5 '(
(  0 10 11 10  9)
( 10  0 11  9 12)
( 11 11  0 11 11)
( 10  9 11  0  5)
(  9 12 11  5  0)))
                  


;; 6 city problem
(define cities6 '(
(  0  3 10  5  6 10)
(  3  0  5  3 11  6)
( 10  5  0  8  5  5)
(  5  3  8  0  7  6)
(  6 11  5  7  0 12)
( 10  6  5  6 12  0)
))
                  
	  
;; 7 city problem
(define cities7 '(
(  0  4  9  3  6  9 11)
(  4  0 10 12  7 12 11)
(  9 10  0  7  6  4 12)
(  3 12  7  0 10  6  4)
(  6  7  6 10  0  7 12)
(  9 12  4  6  7  0  7)
( 11 11 12  4 12  7  0)
))
  

		 

;; 8 city problem

(define cities8 '(
(  0   7   5   8   5  10   5   3 )
(  7   0  10  12   9  12   3   8 )
(  5  10   0   5   8   5   6  12 )
(  8  12   5   0  12   8   4   8 )
(  5   9   8  12   0   7   8   4 )
( 10  12   5   8   7   0   8   3 )
(  5   3   6   4   8   8   0   4 )
(  3   8  12   8   4   3   4   0 )
))
  
;(TSP cities4)
;(TSP cities5)
;(TSP cities6)
;(TSP cities7)
;(TSP cities8)