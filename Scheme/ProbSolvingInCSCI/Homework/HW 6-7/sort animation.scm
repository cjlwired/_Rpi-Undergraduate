;; Carlos Lazo
;; 11-28-04
;; PSiCS - Homework 6/7
;; Sorting Animations

;; SPECIAL NOTES :
;; 
;; For the list to be displayed and sorted correctly, two conditions should be satisfied. The elements of the list should all be positive (> 0)
;; and every element should be no greater than 50. Also, for displaying purposes, the list should be around 30 or less. Also, the displaying
;; of the sort is done within the actual sort. All that is needed is that you call the sort with a list. Tests have been provided in the code.
;; All of the sorts have been implemented correctly and have been tested prior to any display modification. If you need to change the delay of 
;; time when the screen clears, it can be done within the display-sort function. I cleared the sorting window within the sort themselves to 
;; prevent the last pass from being cleared by the display-sort function.

;; NOTICE : Although my quick sort is implemented correctly, I could NOT get it to function with my display mechanism.
;;          Uncomment the test code to try out the program.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; A circle is being defined here, having a center, a radius, and a color.

(define-struct circle (center radius color))

;; A square will be used to clear the canvas.

(define-struct square (center size color))

;; Parameters for graphics window are defined here,

(define LENGTH 1500)
(define WIDTH  1500)

(start LENGTH WIDTH)

(define (display-sort alon)
  (local
      (
       
       ;; This will be the main function that will display the list as a representation of circles. The list itself along with the y value is sent so
       ;; that each individual element of the list is displayed below the other. The y value will be incremented accordingly.
       
       (define (display-step alon y)
         (local
             (
              
              ;; This is the current element that will be used in drawing.
              
              (define elem (first alon))
              
              ;; This function will be used to create a list of elements utilizing the first element of the list as the 
              ;; limiting value. Once the counter reaches zero, cease creating these circles. Note that the x-variable here
              ;; can be changed to increase the distance between the circles that are displayed.
              
              (define (create-circles elem counter x)
                (cond
                  [(= elem counter) empty]
                  
                  ;; Note that the color of the circles can be changed here.
                  
                  [else (cons (make-circle (make-posn x y) 10 'blue) (create-circles elem (+ counter 1) (+ x 25)))]
                  ))
              
              ;; This list created here will store all of the circles in a list for drawing. The number being sent here
              ;; is to have the first circle displayed past the left border of the screen.
              
              (define list-of-circles  (create-circles elem 0 25))
              
              ;; This function will take a circle and draw the circle. It draws concentric circles within itself
              ;; until it gets to the threshold value of 0.
              
              (define (draw-a-circle x)
                (cond
                  [(<= (circle-radius x) 0) true]
                  [else 
                   (and
                    (draw-circle (circle-center x) (circle-radius x) (circle-color x))
                    ;; You can change how much it shrinks right here. If you want no inner circles to be drawn, change the number to a 0.
                    (draw-a-circle (make-circle (circle-center x) (- (circle-radius x) 4) (circle-color x))))]))
              
              ;; This display function goes through and prints out each of the circles in the list given.
              
              (define (display-circles aloc)
                (cond
                  [(empty? aloc) true]
                  [else
                   (and
                    (draw-a-circle (first aloc))
                    (display-circles (rest aloc)))])))
           
           ;; Here, all of the elements in the list undergo a process of having a circular representation created of themselves. 
           
           (cond 
             [(empty? (rest alon)) (display-circles list-of-circles)]
             [else
              (and
               (display-circles list-of-circles)
               (display-step (rest alon) (+ y 30)))]))))
    
    (and
     
     ;; The y-value is 25 to ensure that the first circles displayed are not touching the top border of the draw window.
     (display-step alon 25)
     
     ;; Here, you can change the delay that you want between each pass of the sort
     (sleep-for-a-while 1)
     )))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Here is my implementation of the standard Bubble Sort. It goes through the list n times, where n is the size of the list, and compares
;; one adjacent element to another. If the second is smaller the first, then they switch places. This algorithm takes n-1 passes to complete
;; and is O (n*n).


(define (bubble-sort alon)
  (local
      (
       
       ;; Here, not only does the variable n tell you the size of the list, but it will also be used to
       ;; keep track of the maximum number of passes that the bubble sort will go through.
       
       (define n
         
         (local
             (
              (define (count-elems alon counter)
                (cond
                  [(empty? alon) counter]
                  [else (count-elems (rest alon) (+ counter 1))])))
           
           (count-elems alon 0)))
       
       ;; This counter will be used to tell the sort how many passes it must undergo to ensure 
       ;; that the list will be sorted.
       
       (define counter 0)
       
       ;; Here, the actual sort function is being defined along with all of the necessary helper functions
       ;; and variables that are necessary to make it work.
       
       (define (sort alon n counter)
         
         (local
             (
              
              ;; This variable will be used to keep of where the swapping is occuring in the list
              ;; and when exactly this pass needs to end.
              
              (define pointer 0)
              
              ;; This function called one-pass takes care of one-pass through the bubble sort. It compares
              ;; each element with the other, and adds the correct one into the list. It also account for the
              ;; last element which is never sorted in the end in the base case.
              
              (define (one-pass alon pointer n)
                (cond
                  [(>= pointer (- n 1)) (cons (first alon) empty)]
                  [(> (first alon) (first (rest alon)))
                     (cons (second alon) (one-pass (cons (first alon) (rest (rest alon))) (+ 1 pointer) n))]
                  [else (cons (first alon) (one-pass (rest alon) (+ 1 pointer) n))]))
              
              (define sorted-list (one-pass alon pointer n)))
         
          ;; Here, the list keeps sorting itself until it has gone through n-1 passes.
           
          (cond
            [(= counter (- n 1)) (display-sort sorted-list)]
            [else 
             (and 
              (display-sort sorted-list)
              
              ;; Clears the screen
              (draw-solid-rect (make-posn 0 0) 1500 1500 'white)
              
              (sort sorted-list n (+ 1 counter)))]))))
    
    (sort alon n counter)))
       
; TEST
;(bubble-sort '(6 4 2 2 5 9 3 1 9 4 5 3 2 6 6 11 20 15 9 50 6 4 2 2 5 9 3 1 9 4))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Here is my implementation of the standard Selection Sort. This sort searches for the largest element in the list. It then proceeds
;; to swap that element with the last element of the list. For the next swap to occur, the last element from the previous list must be
;; left untouched. I used a counter to swap the largest element with one less than the current "list length" of the last pass of the 
;; sort. That way, all sorted large elements would be left at the end. This is an O(n) sort that has n^2 comparisons.

(define (selection-sort alon)
  (local
      (
       
       ;; Here, the variable n tells you how many passes this sort must call itself.
       
       (define n
         
         (local
             ( 
              (define (count-elems alon counter)
                (cond
                  [(empty? alon) counter]
                  [else (count-elems (rest alon) (+ counter 1))])))
           
           (count-elems alon 0)))
       
       ;; This counter will be used as a limiting agent to work along with the sorts.
                                                                             
       (define counter 0) 
       
       ;; This is the definition of the sorting algorithm. All of the documentation is within this function.
        
       (define (sort alon n counter)
         
         (local
             (
              
             ;; This function max-elem searches through the list and finds the smallest element in the current list.
               
              (define max-elem
                (local
                    (
                     
                     ;; This will defined variable will limit the amount of times that the selection sort can travel through
                     ;; the list to find the largest element, since some of the elements at the end of the list may already 
                     ;; be sorted.
                     
                     (define max-steps (- n counter))
                     
                     ;; This function helps define a variable that stores the largest element in the list. It utilizes the 
                     ;;above limiting value to ensure that it does not take an element that has already been sorted.
                     
                     (define (find-max-elem alon elem count)
                       (cond
                         [(= count 0) elem]
                         [(> (first alon) elem) (find-max-elem (rest alon) (first alon) (- count 1))]
                         [else (find-max-elem (rest alon) elem (- count 1))])))
                  
                   (find-max-elem alon (first alon) max-steps)))
              
              ;; This variable is being defined using a local scope. It creates a list where the last element of the list
              ;; that hasn't already been swapped (kept track of using a counting variable and the logic of n - counter) 
              ;; is switched with the greatest element found in the previous list.
              
              (define one-pass-list
                (local
                    (
                     
                     ;; This variable will be used to find the location of the greatest element without worrying
                     ;; about elements that have already been sorted.
                     
                     (define max-elem-loc (- n counter 1))
                     
                     ;; This function defines a variable that holds the value of the element that is currently at the 
                     ;; place of one less than the last element that was "sorted."
                     
                     (define (find-old-max-elem alon count)
                       (cond
                         [(= count 0) (first alon)]
                         [else (find-old-max-elem (rest alon) (- count 1))]))
                     
                     (define old-max-elem (find-old-max-elem alon max-elem-loc))
                     
                     ;; This is the swap loop. This function returns a list where the maximum element found in the list and the element
                     ;; that is rightmost and not sorted are swapped. I used an initialization variable to ensure that only one value
                     ;; be swapped in one pass, since there can be duplicates in the list. Once the max-elem is found, I replace it with 
                     ;; the old-max-elem. And finally, once the recursive calls get the count at 0, I just add the maximum element to the
                     ;; list along with the already sorted list.

                     
                     (define (swap-list alon max-elem init count)
                       (cond
                         [(= count 0) (cons max-elem (rest alon))]
                         [(and (= (first alon) max-elem) (= init 0)) (cons old-max-elem (swap-list (rest alon) max-elem 1 (- count 1)))]
                         [else (cons (first alon) (swap-list (rest alon) max-elem init (- count 1)))])))
                  
                  (swap-list alon max-elem 0 max-elem-loc))))
           
           ;; Here, the list sorts itself for n-1 passes. The sort is displayed, and then the list is sorted once again.
           
           (cond 
             [(= counter (- n 1)) (display-sort one-pass-list)]
             [else
              (and
               (display-sort one-pass-list)
               
               ;; Clears the screen
               (draw-solid-rect (make-posn 0 0) 1500 1500 'white)
               
               (sort one-pass-list n (+ 1 counter)))]))))
             
                       
    (sort alon n counter)))

; TEST
(selection-sort '(6 4 2 2 5 9 3 1 9 4 5 3 2 6 6 11 20 15 9 50 6 4 2 2 5 9 3 1 9 4))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Here is my implementation of the standard Quick Sort. Most of the code from here was taken from the quick-sort code that
;; we worked on as a whole in class. The order of magnitude here should be n log n in the best situation. I modified the code
;; a bit to account for repetitions. You can send a relational operator to this code, just like in the standard quick sort 
;; in Scheme. Details will be further explained in the code.

(define (quick-sort alon relop)
  (cond
    
    ;; Base case - When the list is empty, append empty to the list.
    
    [(empty? alon) empty]
    [else
     (local
         (
          
          ;; Using a local scope, I defined three functions that would be used to relate the pivot, which is the (first alon),
          ;; to the other elements in the list. The less-than list will be appeneded before pivot, and as you can guess, the 
          ;; greather-than list will be appended to the right of the pivot. In order to account for any repetitions in the list,
          ;; the pivot in the middle will not only be the one instance of the element found, but ALL instances of it. That is 
          ;; why I created the equal-to.
          
          (define (less-than elem) (relop elem (first alon)))
          (define (greater-than elem) (relop (first alon) elem))
          (define (equal-to elem) (= elem (first alon))))
       
       ;; This is almost identical to the code done in class, except now the relational operator is sent along with the recursive
       ;; call to the quick-sort function.
       (append
          (quick-sort (filter less-than alon) relop)
          (filter equal-to alon)
          (quick-sort (filter greater-than alon) relop)))]
    
    ))
       
; TEST
;(quick-sort '(5 6 6 3 1 2 0 2 0 0 6 6 6 3 2 2) <)
                 
              
              
                                                                                                      



  
  