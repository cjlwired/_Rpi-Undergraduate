%% Carlos Lazo
%% 11/9/2006
%% Artificial Intelligence
%% Homework 4

%% Find the sum of the elements of list.

sum([],0).
sum([H|T], N) :- sum(T,S), N is S+H.

%% Begin to declare the solve function.

   %% First declare the base case to see if the sum of the list is 1.
   %% If it is, then return Yes - the board is solvable.

solve(List) :- sum(List, 1).

solve(List) :-
            append(Head,[1|[1|[0|Tail]]],List),
            append(Head,[0|[0|[1|Tail]]],List_Change),

            %write(List),write("========>"),write(List_Change),nl,fail.
            
            solve(List_Change).
            
solve(List) :-
            append(Head,[0|[1|[1|Tail]]],List),
            append(Head,[1|[0|[0|Tail]]],List_Change),

            %write(Head),write(' '),write(Tail),nl,fail.

            solve(List_Change).
