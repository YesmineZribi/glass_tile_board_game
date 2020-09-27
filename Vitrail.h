#pragma once
#include <vector>
#include <iostream>

using namespace std; 
class Vitrail
{
	//Le vitrail
	char** vitrail; 

	//Tableau de reference aux couleures 
	char c[5]{ 'G','J','B','R','O' };

	//Nombre de cases du vitrail
	int rows;

	//Nombre de colonnes du vitrail
	int columns; 

	//Genere un numero de case aleatoire
	int random_row();

	//Genere un index de couleure aleatoire
	int random_colour();

	

public:
	//Constructeur
	Vitrail(int rows, int columns);

	int construireVitrail(vector<char> vitres, int colonne);

	bool estComplete(int colonne) const;

	bool estEnConstruction(int colonne) const;

	bool estFini() const; 

	//Representation string du vitrail
	const string toString() const;

	//Surchage de l'operateur <<
	inline friend ostream& operator<<(ostream& out, const Vitrail& v)
	{
		out << v.toString();
		return out;

	}

	//Retourne le nombre de cases 
	inline int getRows() const { return rows; }

	//Retourne le nombre de colonnes 
	inline int getColumns() const { return columns; }
	
};

