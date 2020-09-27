#pragma once
#include "Joueur.h"
#include "Lot.h"
#include <iostream>

using namespace std; 

class Partie
{
	Joueur* j1=nullptr; 
	Joueur* j2=nullptr;
	string phaseWinner=""; 
	int currentPhase=-1; 
	string currentWinner=""; //winner of most phases so far
	Joueur* currentPlayer=nullptr; 
	Lot* lot=nullptr; 
	//Flag if a player is done before end of game
	bool done = false; 
	int turn = 0; //Holds the player's turn 
	Lot copyLot; 

public:

	Partie(Joueur* j1, Joueur* j2, Lot* lot);

	inline Joueur& getJoueur1() { return *j1; }
	inline Joueur& getJoueur2() { return *j2; }
	inline int getCurrentPhase() { return currentPhase; }
	inline Lot& getLot() { return *lot; }

	string getPhaseWinner();
	inline string getCurrentWinner() { return currentWinner; }

	inline void setJoueur1(Joueur& j) { j1 = &j;  }
	inline void setJoueur2(Joueur& j) { j2 = &j; }
	inline void setLot(Lot& l) { lot = &l; }


	void start(); 

	void startPhase(); 

	void chooseAction(); 

	void action1();

	void choisiLotEtCouleur(); 

	void choisiColonne(); 

	void action2();


};

