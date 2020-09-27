#include <iostream>
#include <vector>
#include "Vitrail.h"
#include "Joueur.h"
#include "Lot.h"
#include "Partie.h"

int main()
{

	int choice; 
	//Prompt to start game
	cout << "Bienvenue Au Jeu Des Vitrier" << endl;
	cout << "Veuillez choisir l'une des actions suivants: " << endl;
	cout << "(1) Tapez 1 pour commencer une nouvelle partie; ou" << endl;
	cout << "(2) Taper 2 pour quitter" << endl; 
	cout << "Action: " << endl; 
	while (!(cin >> choice) || (choice != 1 && choice != 2)) {
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Je n'ai pas compris votre choix" << endl;
		cout << "Veuillez entrer 1 ou 2 seulement" << endl;
		cout << "Action: ";
	}

	string nom1, nom2;
	while (choice == 1) {
		//1. Demander nom du premier joueur
		cout << "Veuillez entrer le nom du premier joueur!" << endl;
		cout << "Joueur1: ";
		while (!(cin >> nom1)) {
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ce nom n'est pas valide" << endl;
			cout << "Joueur1: ";
		}
		//2. Demander nom du deuxieme joueur
		cout << "Veuillez entrer le nom du deuxieme joueur!" << endl;
		cout << "Joueur2: ";
		while (!(cin >> nom2)) {
			cout << "Ce nom n'est pas valide" << endl;
			cout << "Joueur2: ";
		}

		//3. Creation des deux joueur 
		Joueur j1(nom1, 6, 7);
		Joueur j2(nom2, 6, 7);

		//4. Creation du lot initial
		Lot l;

		//5. Creation d'une partie 
		Partie p(&j1, &j2, &l);

		//6. Debut partie

		p.start();

		cout << "Voulez-vous jouer une nouvelle partie? " << endl;
		cout << "(1) Tapez 1 pour commencer une nouvelle partie; ou" << endl;
		cout << "(2) Taper 2 pour quitter" << endl;
		cout << "Action: " << endl;
		while (!(cin >> choice) || (choice != 1 && choice != 2)) {
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Je n'ai pas compris votre choix" << endl;
			cout << "Veuillez entrer 1 ou 2 seulement" << endl;
			cout << "Action: ";
		}
	} 



	
}


