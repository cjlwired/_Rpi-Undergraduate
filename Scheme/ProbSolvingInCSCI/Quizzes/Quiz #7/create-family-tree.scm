;; Carlos Lazo
;; 10-21-04
;; Quiz #7  -> create-family-tree

(define-struct parent (name children))

;; pclist list is the list of lists that contains all of the parent to child relationships that will be used 
;; in the following function call

(define pclist '( (Joe John)   (Sally John) (Joe Fred)
                  (Sally Fred) (Fred Jane)  (Fred Sam)
                  (Joe George) (Alice Joe)  (Elvis Alice)))

;; create-family-tree takes in the name of the person and the actual list of parent to child comparisons, which is represented 
;; as a list of lists. The end result will return a list which contains all of the parent to child relationships represented
;; within the actual structure.

(define (create-family-tree name list)
  (cond

    ;; If the list of children is empty, add the parent to the tree
    ;; by creating a parent structure, setting its name to the name
    ;; and it's list of children to be empty
    [(empty? list) (make-parent 'name empty)] 
    
    [else
     
     ;; Local scope defined here allowing for multiple function and variable declarations
     (local
         ( ;; find-children takes a name and the list of parent to child relationships. This function searches the 
           ;; the first element of every relationship. If the first element is equal to the name sent to this function, 
           ;; add the corresponding child to a list. Return the complete list at the end. Of course, checking for empty
           ;; is necessary since some of the people do not have children.
           (define (find-children name list)
             (cond
               [(empty? list) empty]
               [else
                (cond
                  [(symbol=? (first (first list)) name) (cons (first (rest (first list))) (find-children name (rest list)))]
                  [else (find-children name (rest list))])]))
           
           ;; create-tree-of-children takes the list of children. It first checks to see if the list is empty, as is the 
           ;; normal base case. Then, this function sends the first element of the list of children back up to create-family-tree 
           ;; to be evaluated. Since all of the children and their children will be evaluated as well, I used the append function to
           ;; also recursively call this function itself with the rest of the list.
           
           (define (create-tree-of-children list )
             (cond
               [(empty? list) empty]
               [else
                (append
                 (create-family-tree (first list) pclist)
                 (create-tree-of-children (rest list)))]))
           
           ;; find-children is a variable that was defined that stores the list of children of a specific person
           ;; within this local scope.
           
           (define loc (find-children name pclist)))
       
           ;; This final evaluation statement begins the entire recursive call of the parents and their respective children.
           ;; The empty at the end serves as the final empty that corresponds to the last list in the tree structure.
           
           (cons (make-parent name (create-tree-of-children loc)) empty))]))


(create-family-tree 'Sam pclist)
(create-family-tree 'Sally pclist)
(create-family-tree 'Joe pclist)
(create-family-tree 'Elvis pclist)
