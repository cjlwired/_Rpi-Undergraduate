%% Carlos Lazo
%% 11/9/2006
%% Artificial Intelligence
%% Homework 4 (with Extra Credit)

%% Find the sum of the elements of list. If the sum of the elements is 1,
%% then the list is solvable.

sum([],0).
sum([Head|Tail], N) :- sum(Tail,S), N is S+Head.

%% Begin to declare the solve function.

   %% First case - declare the base case to see if the sum of the list is 1.
   %% If it is, then return Yes - the board is solvable.

solve(List) :- sum(List, 1).

   %% Second case - have Prolog find and return all parsed lists that have the
   %% sequence [1,1,0] in them. Save the appropriate lists in Head and Tail
   %% variables. Then compile a new list which is a combination of the Head,
   %% Tail, with the flipped bit sequence in the middle. Recursively call
   %% solve on the new list.
   

solve(List) :-
            append(Head,[1|[1|[0|Tail]]],List),
            append(Head,[0|[0|[1|Tail]]],List_Change),
            
            solve(List_Change),
            
            write(List),write('<========'),write(List_Change),nl.
            
solve(List) :-

   %% Third case - have Prolog find and return all parsed lists that have the
   %% sequence [0,1,1] in them. Save the appropriate lists in Head and Tail
   %% variables. Then compile a new list which is a combination of the Head,
   %% Tail, with the flipped bit sequence in the middle. Recursively call
   %% solve on the new list.
   
            append(Head,[0|[1|[1|Tail]]],List),
            append(Head,[1|[0|[0|Tail]]],List_Change),
            
            solve(List_Change),

            write(List),write('<========'),write(List_Change),nl.
