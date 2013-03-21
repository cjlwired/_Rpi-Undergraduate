;; Carlos Lazo
;; 11-4-04
;; Quiz #9 - GUI Design

;; To preserve encapsulation of this program, the function was written using a local scope

(define (play-number-game guess-me)
  (local
      (
       
       ;; check-guess, taking an event as the argument, assigns a value to the answer message defined below. It first
       ;; checks to make sure that the the contents of the text box is a number. If it is, output the corresponding
       ;; message according to the check statements. If not, print out that it is not a number.
       
       (define (check-guess e)
         (draw-message
          answer
          (cond
            [(number? (string->number (text-contents enter)))
             (cond
               [( = (string->number (text-contents enter)) guess-me) (string-append (text-contents enter) " is Right!")]         
               [( < (string->number (text-contents enter)) guess-me) (string-append (text-contents enter) " is too Low!")]
               [( > (string->number (text-contents enter)) guess-me) (string-append (text-contents enter) " is too High!")])]
            [else
             (string-append (text-contents enter) " is not a number!")])))
       
       ;; Defining variables for use later
       
       (define enter (make-text "Enter your guess and press the button "))
       (define guess-button (make-button "Submit Guess" check-guess))
       (define answer (make-message "New game- make a guess between 0 and 100"))
       )
    
    ;; Actual window is drawn here. First make sure that the guess is a number and that 0 <= guess <= 100.
    (cond
      [( and (number? guess-me) (>= guess-me 0) (<= guess-me 100))
       (create-window
        (list
         (list enter)
         (list guess-button)
         (list answer)))]
      [else (error 'play-number-game "Value inputed into program is not valid.")])))

(play-number-game (floor (random 101)))



