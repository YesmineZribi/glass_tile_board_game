#include "Vitrail.h"
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <vector>

using namespace std; 
//Constructeur
Vitrail::Vitrail(int rows, int columns) : rows(rows),
columns(columns) {
	//Initialization dynamique 
	char* tmp = new char[rows * columns];

	vitrail = new char* [rows];

	for (int i = 0; i < rows; i++) {
		vitrail[i] = &tmp[i * columns];
	}

	//Peuple le vitrail
	char c1, c2;
	int h; 
	int i = 0;

	for (int i = 0; i < columns;  i++) {
		//1. Genere les deux couleures au hasard
		c1 = random_colour();
		c2 = random_colour();

		//2. Genere le nombre h 
		h = random_row(); 

		for (int j = 0; j < h; j++) {
			vitrail[j][i] = c[c1];
		}

		for (int j = h; j < rows; j++) {
			vitrail[j][i] = c[c2];
		}
	}


	
}

//Retourne un index aleatoire representant 
//une couleure aleatoire 
int Vitrail::random_colour() {
	random_device generator;
	mt19937 random_engine(generator());
	uniform_int_distribution<int> distribution(0, 4);

	auto const randomNumber = distribution(random_engine);

	return randomNumber;
}

//Retourn un nombre aleatoire entre 0 et 
//le nombre de cases - 1
int Vitrail::random_row() {
	random_device generator;
	mt19937 random_engine(generator());
	uniform_int_distribution<int> distribution(0, rows-1);

	auto const randomNumber = distribution(random_engine);

	return randomNumber;
}

//Representation du vitrail
const string Vitrail::toString() const {
	stringstream ss(stringstream::in | stringstream::out);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			ss << vitrail[i][j] << " ";
		}
		ss << endl;
	}

	for (int i = columns-1; i >= 0; i--) {
		ss << i << " ";
	}
	ss << endl; 

	return ss.str(); 
}

int Vitrail::construireVitrail(vector<char> vitres, int colonne) {
	//Si colonne deja completee lancer exception 
	if (estComplete(colonne))
		throw std::invalid_argument("Colonne deja complete");
	//Si colonne hors tableau lancer exception
	if (colonne < 0 || colonne > 6) {
		throw std::out_of_range("Numero de colonne invalid");
	}

	auto it = vitres.begin();
	for (int i = 0; i < rows; i++) {
		if (it != vitres.end() && *it == vitrail[i][colonne]) {
			vitrail[i][colonne] = 'x';
			it++;
		}
	}
	if (it != vitres.end()) {
		//Retourne nombre de vitres non-utilisees
		return vitres.end() - it;
	}
	//Si it est arrive a la fin toutes les vitres ont ete utilisees
	return 0; 
	// Do some pointer arithmetic 
}

bool Vitrail::estComplete(int colonne) const {
	for (int i = 0; i < rows; i++) {
		if (vitrail[i][colonne] != 'x') {
			return false;
		}
	}
	return true; 
}


bool Vitrail::estEnConstruction(int colonne) const {
	if (estComplete(colonne))
		return false; 
	for (int i = 0; i < rows; i++) {
		if (vitrail[i][colonne] == 'x') {
			return true;
		}
	}
	return false;
}

//Verifier si tout le vitrail est complete 
bool Vitrail::estFini() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (vitrail[i][j] != 'x')
				return false;
		}
	}
	return true; 
}