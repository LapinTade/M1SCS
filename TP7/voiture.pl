:- use_module(library(lists)).

sntdsdiff(P1,P2):-
	

voisine(P1,P2):-
	P2 is abs(P1 + 1),
	!.
voisine(P1,P2):-
	P2 is abs(P1 - 1),
	!.

solution(S):-
	S = [[1,M1,CO1,CA1,O1,PU1],
	     [2,M2,CO2,CA2,O2,PU2],
	     [3,M3,CO3,CA3,O3,PU3],
	     [4,M4,CO4,CA4,O4,PU4],
	     [5,M5,CO5,CA5,O5,PU5]],
	Puissance = [70,90,120,132,160],
	Modele = [saab,toyota,citroen,rover,bmw],
	Couleur = [rouge,jaune,vert,bleu,blanche],
	Carbu = [sp95,sp98,gpl,super,diesel],
	Opt = [ordi, toit, cd, jantalu,vitres],
	
	%phase1
	member([1,saab,_,_,_,_],S),
	%phase2
	member([2,_,bleu,_,_,_],S),
	%phase3
	member([3,_,_,diesel,_,_],S),
	%phase4
	member([_,rover,rouge,_,_,_],S),
	%phase5
	member([X,_,vert,sp95,_,_],S),
	%phase6
	member([_,_,jaune,_,ordi,_],S),
	%phrase7:
	X2 is X+1,
	member([X2,_,blanche,_,_,_]),
	%phrase8:
	member([_,citroen,_,_,_,132]),
	%phrase9:
	member([_,bmw,_,super,_,_]),
	%phrase10:
	member([_,toyota,_,_,toit,_]),
	%phrase11:
	member([_,_,_,_,vitres,90]),
	%phrase12:
	member([_,_,_,sp98,cd,_]),
	%phrase13:
	member([X3,_,_,_,jantalu,_]),
	voisine(X3,X4),
	member([X4,_,_,_,_,120]),
	voisine(X4,X6),
	%phrase14
	member([X6,_,_,_,_,160]).