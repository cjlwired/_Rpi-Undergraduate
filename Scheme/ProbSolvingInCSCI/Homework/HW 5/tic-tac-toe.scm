;; Carlos Lazo
;; 10-30-04
;; Homework #5 -> Tic-Tac-Toe Player

;; My player, lazoc-player, will use a local scope to define all functions. In depth comments will
;; be written within the function itself.

(define (lazoc-player board me)
  (local
      (
       
       ;; I first define a function called find-opponent which will return the 'ID' of the opponent
       ;; in this specific game.
       
       (define (find-opponent me)
         (cond
           [(= me 1) 2]
           [else 1]))
       
       ;; The 'ID' of the opponent is stored within variable opponent
       
       (define opponent (find-opponent me))
       
       ;; This function here returns the value of the coordinate utilizing a row (r) and column (c)
       ;; coordinate of the board.
       
       (define (coord-value r c board)
         (local
             (
              
              ;; Finds the corresponding r row of the board sent
              
              (define (get-r row board)
                (cond
                  [(= 0 row) (first board)]
                  [else (get-r (- row 1) (rest board))]))
              
              ;; Store the r row found in the board in a variable called r-value
              
              (define r-value (get-r r board))
              
              ;; Take the r-value found out in the previous statement and use it to find the value of the 
              ;; cth element in that row.
              
              (define (get-value row col board)
                (cond
                  [(= 0 col) (first row)]
                  [else (get-value (rest row) (- col 1) board)])))                                      
                      

           ;; Return the value at that coordinate
           
           (get-value r-value c board)))                   
       
    
    (define (find-move board me)
      (local
          (
           
           ;; Function check-for-win-or-block, taking the game board and an 'ID', checks the game board for every and all
           ;; possible win or block situations, depending on the number sent. If one is found, return that location. If not, return empty.
           
           (define (check-for-win-or-block board ID)
             (cond
               
               ;; Checking three possibilities for first row
               
               [(and (= (coord-value 0 0 board) ID) (= (coord-value 0 1 board) ID)  (= (coord-value 0 2 board) 0)) (list 0 2)]
               [(and (= (coord-value 0 0 board) ID) (= (coord-value 0 1 board) 0)  (= (coord-value 0 2 board) ID)) (list 0 1)]
               [(and (= (coord-value 0 0 board) 0) (= (coord-value 0 1 board) ID)  (= (coord-value 0 2 board) ID)) (list 0 0)]
               
               
               ;; Checking three possibilities for second row
               
               [(and (= (coord-value 1 0 board) ID) (= (coord-value 1 1 board) ID)  (= (coord-value 1 2 board) 0)) (list 1 2)]
               [(and (= (coord-value 1 0 board) ID) (= (coord-value 1 1 board) 0)  (= (coord-value 1 2 board) ID)) (list 1 1)]
               [(and (= (coord-value 1 0 board) 0) (= (coord-value 1 1 board) ID)  (= (coord-value 1 2 board) ID)) (list 1 0)]
               
               [(and (= (coord-value 2 0 board) ID) (= (coord-value 2 1 board) ID)  (= (coord-value 2 2 board) 0)) (list 2 2)]
               [(and (= (coord-value 2 0 board) ID) (= (coord-value 2 1 board) 0)  (= (coord-value 2 2 board) ID)) (list 2 1)]
               [(and (= (coord-value 2 0 board) 0) (= (coord-value 2 1 board) ID)  (= (coord-value 2 2 board) ID)) (list 2 0)]
               
               ;; Checking three possibilities for third row
               
               [(and (= (coord-value 0 0 board) ID) (= (coord-value 1 0 board) ID)  (= (coord-value 2 0 board) 0)) (list 2 0)]
               [(and (= (coord-value 0 0 board) ID) (= (coord-value 1 0 board) 0)  (= (coord-value 2 0 board) ID)) (list 1 0)]
               [(and (= (coord-value 0 0 board) 0) (= (coord-value 1 0 board) ID)  (= (coord-value 2 0 board) ID)) (list 0 0)]
               
               ;; Checking three possibilities for first column
               
               [(and (= (coord-value 0 0 board) ID) (= (coord-value 1 0 board) ID)  (= (coord-value 2 0 board) 0)) (list 2 0)]
               [(and (= (coord-value 0 0 board) ID) (= (coord-value 1 0 board) 0)  (= (coord-value 2 0 board) ID)) (list 1 0)]
               [(and (= (coord-value 0 0 board) 0) (= (coord-value 1 0 board) ID)  (= (coord-value 2 0 board) ID)) (list 0 0)]
               
               ;; Checking three possibilities for second column
               
               [(and (= (coord-value 0 1 board) ID) (= (coord-value 1 1 board) ID)  (= (coord-value 2 1 board) 0)) (list 2 1)]
               [(and (= (coord-value 0 1 board) ID) (= (coord-value 1 1 board) 0)  (= (coord-value 2 1 board) ID)) (list 1 1)]
               [(and (= (coord-value 0 1 board) 0) (= (coord-value 1 1 board) ID)  (= (coord-value 2 1 board) ID)) (list 0 1)]
               
               ;; Checking three possibilities for third column
               
               [(and (= (coord-value 0 2 board) ID) (= (coord-value 1 2 board) ID)  (= (coord-value 2 2 board) 0)) (list 2 2)]
               [(and (= (coord-value 0 2 board) ID) (= (coord-value 1 2 board) 0)  (= (coord-value 2 2 board) ID)) (list 1 2)]
               [(and (= (coord-value 0 2 board) 0) (= (coord-value 1 2 board) ID)  (= (coord-value 2 2 board) ID)) (list 0 2)]
               
               ;; Checking three possibilities for top-left to bottom-right diagonal

               [(and (= (coord-value 0 0 board) ID) (= (coord-value 1 1 board) ID)  (= (coord-value 2 2 board) 0)) (list 2 2)]
               [(and (= (coord-value 0 0 board) ID) (= (coord-value 1 1 board) 0)  (= (coord-value 2 2 board) ID)) (list 1 1)]
               [(and (= (coord-value 0 0 board) 0) (= (coord-value 1 1 board) ID)  (= (coord-value 2 2 board) ID)) (list 0 0)]
               
               ;; Checking three possibilities for bottom-right to top-left diagonal

               [(and (= (coord-value 0 2 board) ID) (= (coord-value 1 1 board) ID)  (= (coord-value 2 0 board) 0)) (list 0 2)]
               [(and (= (coord-value 0 2 board) ID) (= (coord-value 1 1 board) 0)  (= (coord-value 2 0 board) ID)) (list 1 1)]
               [(and (= (coord-value 0 2 board) 0) (= (coord-value 1 1 board) ID)  (= (coord-value 2 0 board) ID)) (list 2 0)]
               
               [else empty]))
           
           ;; Defined random-coord as a function that will be used to pick a random open coordinate on the board
           
           (define (random-coord board me)
             (local
                 ((define r (random 3))
                  (define c (random 3)))
               (cond
                 [(= 0 (coord-value r c board)) (list r c)]
                 [ else (random-coord board me)])))
           
           )
        
        ;; This will determine the priority of the above functions.  In other words, they will be run in the order
        ;; defined by the cond stateIDnt below:
        
        (cond 
          
          ;; Checks to see if the board is empty. If it is, then continue through the loop.
          ;; If not, then return the winning element.
          
          [ (empty? (check-for-win-or-block board me))
            
            (cond
              
              ;; Checks to see if the opponent has a winning condition. If empty is returned, then
              ;; choose a random position on the board. If not, block the opponents move.
              
              [(empty? (check-for-win-or-block board opponent)) (random-coord board me)] ;; (list -1 -1) WILL be replaced by make-intelligent-move
              [else (check-for-win-or-block board opponent)])]
                                                        
          [else (check-for-win-or-block board me)])
         
          )))
     
    ;; Runs the main function which will eventually decide what coordinate is returned
     
    (find-move board me)
  
))