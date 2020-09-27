#pragma once
#include <iostream>
#include "Vitrail.h"
#include <vector>

using namespace std; 
class Joueur
{
	string nom; 
	int points=0; 
	int position=0; 
	int phasesWon = 0;
	Vitrail* v=nullptr; 
	vector<char> vitresChoisies;

public:

	//Constructeur 1
	Joueur(string nom, int rows, int columns);
	
	//Constructeur 2 
	Joueur(string nom);

	//Setter pour le vitrail
	inline void setVitrail(Vitrail* v) {
		this->v = v;
	}

	//Setter pour les points
	inline void setPoints(int points) {
		this->points = points; 
	}
	
	//getter pour le nom du joueur
	inline string getNom() { return nom; }

	//getter pour le nombre de phases gagnee
	inline int getPhasesWon() {
		return phasesWon;
	}

	//getter pour la position actuelle
	inline int getPosition() const {
		return v->getColumns() - 1 - position;
	}

	//Getter pour les points
	inline int getPoints() const {
		return points;
	}

	inline Vitrail& getVitrail() const {
		return *v; 
	}

	Joueur& operator--();
	
	//Met joueur a position inc
	Joueur& operator-=(int);

	//Remet joueur a extreme gauche
	inline bool operator~() {
		if (position == 0) {
			return false;
		}
		position = 0;
		return true;
	}

	//Surchage de l'operateur << 
	inline friend ostream& operator<<(ostream& out, const Joueur& j) {
		out << j.toString();
		return out; 
	}

	void wonPhase() {
		phasesWon += 1;
	}
	
	void calculerPoints(int nonUtilis); 

	//Representation du joueur
	string toString() const; 

	//Methode pour recuperer les vitres
	inline void recupererVitres(vector<char> vitres) {
		vitresChoisies = vitres; 

	}

	//Construit vitrier from vitresChoisies
	//Caluclate points 
	void play(); 

	//Destructeur 
	inline ~Joueur() { delete v; }
	

};

