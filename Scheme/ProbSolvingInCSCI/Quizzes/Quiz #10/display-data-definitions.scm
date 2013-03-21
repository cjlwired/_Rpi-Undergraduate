;; Carlos Lazo
;; 11-12-04
;; Quiz #10 - Data Definitions

;; 1) Sorting:
;;
;; I know for a fact that I will be using quicksort along with one of the other two sorts. If possible, I will add more.
;; They will all be defined before the definition of the interface that will take care of the display. All of the definitions
;; will take a list of objects and a relational operator that will be used to sort them.

;; 2) Display Interface:
;;
;; I am pretty sure that I will be making a GUI for the display. The GUI itself will contain a textbox wear one can enter a list.
;; The GUI will check that the list is valid. Once the list is entered, the user will then be able to select a few choices which will
;; represent the several sorts. Each of the sorts will be accessed by buttons. Once a button is clicked , the program will proceed to 
;; draw a graphical representation of what the sort is doing. It will therefore print on the GUI the list in sorted order.
;;
;; (display-sort-animation
;;  (create-window
;;   (list
;;    (list ......)
;;    (list ......))))
;;
;; * Of course, all of the buttons, text boxes, and message will be properly defined. The sorting functions will be used as special 
;; call-back functions which will then proceed to display the algorithm as it is processing and sorting the list.

;; 3) Display Function
;;
;; When a button is pressed, it will instantiate the algorithm of the desired sort. I will try to implement this so that this call-back
;; display function is sent a parameter which will indicate which sort should be used so as to minimize the amounts of functions that will 
;; be called. Once the function begins to execute, the sort will process the list accordingly and it will display the state of the sort in some
;; graphical manner (not determined yet) after every pass. The sorts themselves will know how many times the function must be called. I think
;; that many local scopes will be used in the implementation of this function. I have not yet decided how I will compare the actual sorts within
;; the display function - I will probably differentiate them with strings.
;;
;; (display-sort-animation
;;  (create-window
;;   (list
;;    (list ...)
;;    (list (make-button ... (display "quicksort"))))))



   




    
            
            