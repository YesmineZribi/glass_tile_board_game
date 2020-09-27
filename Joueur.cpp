#include "Joueur.h"
#include <iostream>
#include <sstream>

Joueur::Joueur(string nom, int rows, int columns) : nom(nom), points(0), position(0) {
	//Vitrail alloue dynamiquement 
	v = new Vitrail(rows, columns);
}

Joueur::Joueur(string nom) : nom(nom), points(0),position(0){}

//Deplace une position la droite 
Joueur& Joueur::operator--() {
	position++;
	return *this;
}

//Deplace vers colonne 
Joueur& Joueur::operator-=(int inc) {
	if (inc >= v->getColumns() || inc < 0)
		throw std::out_of_range("Vous avez tente de vous deplacer en dehors du vitrail");


	int num = v->getColumns()-1 - inc; 
	if (num < position) {
		string msg = "Vous ne pouvez travailler que sur des colonnes entre 0 et " + to_string(getPosition());
		throw msg;
	}
	//1. Deplacer vitrier 
	position = num; 

	//2. Jouer:
	play();

	return *this;
}


//Representation du joueur
string Joueur:: toString() const {
	stringstream ss(stringstream::in | stringstream::out);
	ss << "Joueur " << nom << ": " << points << " points" << endl; 
	ss << "Vitrier a la position " << getPosition() << endl;
	ss << "Plan: " << endl;
	ss << *v; 
	return ss.str(); 
}


void Joueur::calculerPoints(int nonUtilisees) {
	if (v->estComplete(position)) {
		//3 points for completing the whole column
		points += 3; 
		int columns = v->getColumns();
		//Make sure not the last column if looking
		//at right adjacent columns
		if (position < columns - 1) {
			for (int i = position + 1; i < columns; i++) {
				if (v->estEnConstruction(i)) {
					//1 point for each column started 
					points += 1;
				}
			}
		}

	}

	//Remove points for the remaining vitres 
	while (nonUtilisees > 0 && points > 0) {
		points -= 1;
		nonUtilisees--;
	}
}

void Joueur::play() {
	//1. Construit Vitrail from vitresChoisies
	int reste = v->construireVitrail(vitresChoisies,position);
	//2. Calculer les points
	calculerPoints(reste);
}