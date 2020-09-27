#include "Lot.h"
#include <random>
#include <iostream>
#include <sstream>
using namespace std; 

//Constructeur qui peuple le lot 
Lot::Lot() : random_engine(random_device()())
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			//Peuple le lot de facon aleatoire
			lot[i][j] = generate_random_colour();
		}
	}
}
//Retourne vrai si le lot est vide 
bool Lot::estVide() const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (lot[i][j] != '.') {
				return false; 
			}
		}
	}
	if (surplus.begin() != surplus.end())
		return false; 

	return true;
}

//Representation du lot 
string Lot::toString() const {
	stringstream ss(stringstream::in | stringstream::out);
	ss << "Lots: " << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			ss << lot[i][j] << " ";
		}
		ss << endl; 
	}

	for (int i = 5 - 1; i >= 0; i--) {
		ss << i << " ";
	}
	ss << endl; 
	ss << "Surplus: " << endl; 
	ss << "[";
	for (auto i = surplus.begin(); i != surplus.end(); i++)
		ss << *i << " ";
	ss << "]" << endl; 

	return ss.str();
}

//reset le lot et surplus
void Lot::reset() {
	//reset lot 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			//Peuple le lot de facon aleatoire
			lot[i][j] = generate_random_colour();
		}
	}

	surplus.clear(); 
}

vector<char> Lot::ramasseVitre(char couleur, int numeroLot) {
	//Si couleur n'appartient pas a c erreur 
	bool valid = false;
	for (int i = 0; i < 5; i++) {
		if (c[i] == couleur)
			valid = true; 
	}
	if (!valid) {
		throw invalid_argument("La couleur n'exist pas");
	}

	//Si numeroLot > 5 erreur 
	if (numeroLot >= 5) {
		throw invalid_argument("Le numero de lot est invalide");
	}

	//Si numeroLot < 0 ramasser vitres dans surplus
	vector<char> vitresChoisies; 
	if (numeroLot < 0) {
		//Mais si surplus vide erreur 
		if (surplus.begin() == surplus.end()) {
			throw invalid_argument("Vous ne pouvez pas choisir vos vitres du surplus car il est vide");
		}

		//Si couleur choisies pas dans surplus erreur 
		bool found = false; 
		for (auto i = surplus.begin(); i != surplus.end(); i++) {
			if (*i == couleur) {
				found = true;
			}
		}
		if (!found) {
			throw invalid_argument("La couleur choisie ne se trouve pas dans le surplus");
		}
		auto it = surplus.begin(); 
		while (it != surplus.end()) {
			if (*it == couleur) {
				vitresChoisies.push_back(couleur);
				it = surplus.erase(it);
			}
			else {
				it++;
			}
		}
	}
	else { //Sinon ramasser vitres dans numeroLot
		int pos = 4 - numeroLot;
		//Verifier si le lot n'a pas deja ete pris
		if (lot[0][pos] == '.') {
			throw invalid_argument("Ce lot est vide");
		}

		//Verifier que la couleur prise se trouve dans lot
		bool found = false; 
		for (int i = 0; i < 4; i++) {
			if (lot[i][pos] == couleur) {
				found = true; 
			}
		}
		if (!found) {
			throw invalid_argument("Veuillez choisir seulement une couleur disponible dans le lot");
		}
			
		char current; 
		for (int i = 0; i < 4; i++) {
			current = lot[i][pos];
			if(current == couleur) {
				vitresChoisies.push_back(couleur);
				
			}
			else {
				surplus.push_back(current);
			}
			lot[i][pos] = '.';
		}
	}

	return vitresChoisies; 
}

//Surcharge de l'operateur= 
Lot& Lot::operator=(const Lot& o) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			lot[i][j] = o.lot[i][j];
		}
	}
	surplus = o.surplus; 
	return *this;
}

//Remplace les couleurs sur numLot avec celles dans vitres
void Lot::setColonne(vector<char> vitres, int numLot) {
	int pos = 4 - numLot; 
	for (int i = 0; i < 4; i++) {
		lot[i][pos] = vitres[i];
	}
}

//Retourne la list de vitres dans la colonne numLot 
vector<char> Lot::getColonne(int numLot) {
	int pos = 4 - numLot; 
	vector<char> col;
	for (int i = 0; i < 4; i++) {
		col.push_back(lot[i][pos]);
	}
	return col; 
}
