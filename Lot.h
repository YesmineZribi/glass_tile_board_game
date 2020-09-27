#pragma once
#include <vector>
#include <iostream>
#include <random>
using namespace std; 

class Lot
{
	char lot[4][5]; 
	vector<char> surplus; 
	mt19937 random_engine;

	//Tableau de reference aux couleures 
	char c[5]{ 'G','J','B','R','O' };

public:
	Lot();

	vector<char> ramasseVitre(char couleur, int numeroLot);

	void setColonne(vector<char> vitres, int colonne);

	inline void setSurplus(vector<char> surplus) {
		this->surplus = surplus;
	}

	inline vector<char> getSurplus() {
		return surplus;
	}

	vector<char> getColonne(int colonne);

	void reset(); 

	//Genere une couleur de c de facon aleatoire 
	inline char generate_random_colour() {
		uniform_int_distribution<int> distribution(0, 4);
		return c[distribution(random_engine)];
	}

	bool estVide() const;

	string toString() const;

	//Afficheage de la class 
	friend inline ostream& operator<<(ostream& out, const Lot& l) {
		out << l.toString(); 
		return out;
	}

	Lot& operator=(const Lot& o);


};

