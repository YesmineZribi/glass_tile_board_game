#include "Partie.h"

Partie::Partie(Joueur* j1, Joueur* j2, Lot* lot) :
	j1(j1), j2(j2), lot(lot) {
}

//Retourne le nom du gagnant de cetter partie
//Ou une chaine de charactere vide si c'est un tie 
string Partie::getPhaseWinner() {
	int p1 = j1->getPoints();
	int p2 = j2->getPoints();
	if (p1 > p2) {
		return j1->getNom();
	}
	else if (p1 == p2) {
		return " ";
	}
	else {
		return j2->getNom();
	}
}

void Partie::start() {
	//2. Set currentPhase a 0 
	currentPhase = 0; 

	// while currentPhase < 5
	while (!done && currentPhase < 5) {
		cout << "Debut de nouvelle phase" << endl;
		//3. startPhase
		startPhase(); 

		//Reset le lot 
		this->lot->reset();
		currentPhase++;
	}

	if (done) {
		cout << "Le gagnant est " << currentWinner << endl; 
	}

	//End of game, declare winner 
	else if (currentPhase >= 5) {
		if (j1->getPoints() > j2->getPoints()) {
			cout << "Le gagnant est: " << j1->getNom() << endl; 
		}
		else if (j1->getPoints() < j2->getPoints()){
			cout << "Le gagnant est: " << j2->getNom() << endl;
		}
		else {
			cout << "C'est un tie personne n'a gagne" << endl; 
		
		}

	}

}

//Entame le jeu durant une phase
void Partie::startPhase() {
	cout << "Debut de Phase: " << currentPhase << endl; 

	while (!lot->estVide()) {
		if (turn % 2 == 0) {
			currentPlayer = j1;
		}
		else {
			currentPlayer = j2;
		}
		//Afficher joueur 
		cout << *currentPlayer << endl; 

		//Afficher lot
		cout << *lot << endl; 

		//Proposer deux actions: 
		cout << "A votre tour " << currentPlayer->getNom() << "!" << endl;
		chooseAction();

		//Check if the current player's board is not full 
		if (currentPlayer->getVitrail().estFini()) {
			currentWinner = currentPlayer->getNom(); 
			done = true; //signaler fini 
			break; 

		}
		cout << "------------" << endl;
		//Passer tour au prochain joueur 
		turn++;
	}




}

void Partie::chooseAction() {
	//Holds current player's choice 
	int choice; 
	cout << "Voulez-vous:" << endl;
	cout << "(1) Choisir des vitres; ou" << endl;
	cout << "(2) Replacer vitrier sur colonne de gauche" << endl;
	cout << "Entrez 1 ou 2 quand vous aurez fait votre choix!" << endl;
	cout << "Action: ";
	//Handle invalid input 
	while (!(cin >> choice) || (choice != 1 && choice != 2)) {
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Je n'ai pas compris votre choix" << endl;
		cout << "Veuillez entrer 1 ou 2 seulement" << endl;
		cout << "Action: ";
	}

	//1) S'approprier des vitres: Appeler action1()
	if (choice == 1) {
		action1();
	}

	//2) Replacer vitrier a colonne 6: Appeler action2()
	if (choice == 2) {
		action2();
	}
}
//Processus a suivre si joueur decide de 
//s'approprier vitres
void Partie::action1() {

	choisiLotEtCouleur();
	choisiColonne();
}

void Partie::choisiLotEtCouleur() {
	int lotNum;
	char color;
	bool validLot = true;
	//1. Demander a joueur de choisir un lot et une couleur
	cout << "Choisissez un numero de lot ou le surplus: ";
	while (!(cin >> lotNum)) {
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Je n'ai pas compris votre choix" << endl;
		cout << "Veuillez choisir un numero de lot entre 0 et 4 ou un nombre negatif pour le surplus: ";
	}
	cout << "Choisissez une couleur: ";
	while (!(cin >> color)) {
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Je n'ai pas compris votre choix" << endl;
		cout << "Veuillez choisir une des 5 couleures: {G,J,B,R,O}: ";
	}
	//Recuperer les vitres choisies 
	try {

		//Store current state of lot in case we need to restore
		copyLot = *lot; 

		currentPlayer->recupererVitres(lot->ramasseVitre(color, lotNum));

	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
		cout << "Veuillez entrer des choix valid!" << endl;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		choisiLotEtCouleur();
	}
}

void Partie::choisiColonne() {
	//2. Demander a joueur de choisir une colonne -> Deplace vitrier vers colonne choisie / jouer
	// et calculer les points
	int colonne;
	cout << "Choisissez un numero de colonne: ";
	while (!(cin >> colonne)) {
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Je n'ai pas compris votre choix" << endl;
		cout << "Veuillez choisir un numero de colonne valide: ";
	}
	try {
		(*currentPlayer) -= colonne;
		cout << *currentPlayer << endl;
		cout << *lot << endl; 
	}
	catch (out_of_range e) {
		cout << e.what() << endl; 
		cout << "Veuillez reessayer" << endl;
		choisiColonne(); 
	}
	catch (invalid_argument e1) {
		cout << e1.what() << endl;
		cout << "Veuillez reessayer" << endl;
		choisiColonne();
	}
	catch (string msg) {
		//Exception quand joueur tente de choisir 
		//une colonne a gauche 
		cout << msg << endl;
		cout << "Veuillez reessayer" << endl;
		//choisiColonne();
		//In this case: restore lot and surplus 
		*lot = copyLot; 
		//Call back choice of actions 
		chooseAction(); 
	}
}

//Processus a suivre si joueur decide de repositionner sur colonne 6 
void Partie::action2() {
	//1. Si replacement retourne faux demander a joueur de choisir action 1 
	bool valide = ~(*currentPlayer);
	if (!valide) {
		cout << "Vous etes deja a la position 6" << endl; 
		cout << "Veuillez recuperer des vitres" << endl;
		action1();
	}
	else {
		cout << *currentPlayer << endl; 
		cout << *lot << endl;

	}
}
