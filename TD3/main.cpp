/**
* Programme qui comprend la surcharge d'operateur << et qui comrepnd tous les
* tests demandes dans l'enonce.
* \file   main.cpp
* \author Laurie Bedard-Cote (2086165) et Mathias Gagnon (2115246)
* \date  24 octobre 2021
* \cree  6 octobre 2021
*/

#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "Liste.hpp"
#include "Concepteur.hpp"
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include <iostream>
#include <fstream>
using namespace std;

//TODO: Vos surcharges d'opérateur <<

ostream& operator<< (ostream& os, const Liste<Concepteur>& lc) 
{
	
	for (auto i : iter::range(lc.size())) {
		os << "\t" <<lc[i]->getNom() << ", " << lc[i]->getAnneeNaissance() 
		   << ", " << lc[i]->getPays() << endl;
	}
	return os;
}

ostream& operator<< (ostream& os, const Liste<Jeu>& lj)
{
	for (auto i : iter::range(lj.size())) {
		os << lj[i]->getTitre() << endl << lj[i].get()->getAnneeSortie()  
		   << endl << lj[i]->getDeveloppeur() << endl;
		
		os << *lj[i]->getConcepteurs() << endl;	
	}

	return os;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion
	
	Liste<Jeu> lj = creerListeJeux("jeux.bin");
	static const string ligneSeparation = "\n\033[92m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";

	
	//TODO: Les l'affichage et l'écriture dans le fichier devraient fonctionner.
	cout << ligneSeparation << lj;
	//ofstream("sortie.txt") << lj;

	//TODO: Compléter le main avec les tests demandés.
	cout << ligneSeparation << endl;
	// Devrait avoir 17 jeux
	cout << "Nb de jeux : " << lj.size()		<< endl; 
	// Devrait avoir une capacite de 32
	cout << "Capacite : "   << lj.getCapacite() << endl; 
	
	// Devrait avoir "Secret of Mana"
	cout << "Titre du jeu a l'indice 2 : " << lj[2]->getTitre() << endl; 
	// Devrait avoir "Hiromichi Tanaka"
	cout << "Nom du deuxieme concepteur du jeu a l'indice 2 : " 
		 << lj[2]->getConcepteurs()->operator[](1)->getNom() << endl; 
	
	std::string nom = "Yoshinori Kitase";
	auto testNom	= [&](shared_ptr<Concepteur> c) {return c->getNom() == nom; };

	shared_ptr<Concepteur> resultatJ0 = lj[0]->chercherConcepteur(testNom);
	shared_ptr<Concepteur> resultatJ1 = lj[1]->chercherConcepteur(testNom);

	cout << "Recherche de concepteur du nom 'Yoshinori Kitase' dans le jeu 0: " 
		 << resultatJ0  << "  Annee de naissance : " 
		 << resultatJ0->getAnneeNaissance() << endl;
	cout << "Recherche de concepteur du nom 'Yoshinori Kitase' dans le jeu 1: " 
		 << resultatJ1 << "  Annee de naissance : " 
		 <<  resultatJ1->getAnneeNaissance() << endl;

	
	
	// 
	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}