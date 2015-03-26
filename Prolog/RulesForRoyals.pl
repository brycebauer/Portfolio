% Bryce Bauer
% CSCI 305 Lab 4
:-  consult('royal.pl').


mother(M,C):- parent(M,C), female(M).
father(M,C):- parent(M,C), male(M).
spouse(M,C):- married(C,M);  married(M,C).
child(M,C):- parent(C,M).
son(M,C):-  child(M,C), male(M).
daughter(M,C):- child(M,C), female(M).
sibling(M,C):- mother(P,C), parent(P,M), M\=C.
brother(M,C):- sibling(M,C), male(M).
sister(M,C):- sibling(M,C), female(M).
uncle(M,C):- male(M), sibling(M,Z), parent(Z,C).
uncle(M,C):- male(M), spouse(C,Z), parent(L,Z), sibling(M,L).
aunt(M,C):- female(M), sibling(M,Z), parent(Z,C).
aunt(M,C):- female(M), spouse(C,Z), parent(L,Z), sibling(M,L).
grandparent(M,C):- parent(M,Z), parent(Z,C).
grandfather(M,C):- grandparent(M,C), male(M).
grandmother(M,C):- grandparent(M,C), female(M).
grandchild(M,C):- child(Z,C), child(M,Z).
descendent(M,C):- parent(C,M).
descendent(M,C):- parent(Z,M), descendent(Z,C).
ancestor(M,C):- descendent(C,M).
older(M,C):- born(M,Z), born(C,D), Z < D.
younger(M,C):- born(M,Z), born(C,D), Z > D.
regentWhenBorn(M,C):- reigned(M, B, E), born(C,Z), B =< Z, Z =< E.











