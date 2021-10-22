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
		os << "\t" <<lc[i]->getNom() << ", " << lc[i]->getAnneeNaissance() << ", " << lc[i]->getPays() << endl;
	}
	return os;
}

ostream& operator<< (ostream& os, const Liste<Jeu>& lj)
{
	for (auto i : iter::range(lj.size())) {
		os << lj[i]->getTitre() << endl << lj[i].get()->getAnneeSortie()  << endl
		<< lj[i]->getDeveloppeur() << endl;
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
	//cout << ligneSeparation << lj;
	ofstream("sortie.txt") << lj;

	//TODO: Compléter le main avec les tests demandés.
	cout << "Nb de jeux : " << lj.size() << endl; // Devrait avoir 17 jeux
	cout << "Capacite : " << lj.getCapacite() << endl; // Devrait avoir une capacite de 32
	cout << "Titre du jeu a l'indice 2 : " << lj[2]->getTitre() << endl; // Devrait avoir "Secret of Mana"
	cout << "Nom du concepteur du jeu a l'indice 2 : " << lj[2]->getConcepteurs()->operator[](1)->getNom() << endl; // Devrait avoir "Hiromichi Tanaka"


	cout << ligneSeparation << lj;

	cout << ligneSeparation << endl;
	
	// Test de la copie (#7)

	auto jeu0 = lj[0];
	auto jeu1 = lj[1];
	auto jeu2 = lj[2];
	Jeu nouveauJeu = *jeu2;
	cout << jeu2 << "\n" << &nouveauJeu << endl;

	nouveauJeu.getConcepteurs()->operator[](1) = jeu0->getConcepteurs()->operator[](1);
	//
	cout << ligneSeparation << nouveauJeu.getConcepteurs()->operator[](1).get()->getNom() << endl;
	
	cout << "Jeu 2 : " << jeu2->getTitre() << endl;
	cout << *jeu2->getConcepteurs() << endl;
	cout << "Copie modifiee : " << nouveauJeu.getTitre() << endl;
	cout << *nouveauJeu.getConcepteurs() << endl;
	cout << "Adresse premier concepteur jeu2 : " << jeu2->getConcepteurs()->operator[](0) << " \t Adresse premier concepteur copie : " << nouveauJeu.getConcepteurs()->operator[](0) << endl;

	//auto j = lj.trouverCritere(lj&,  [](unique_ptr<Jeu> e) {return e = jeu2->getTitre() });
	char c = 'M';
	auto a = lj.trouverCritere([&](shared_ptr<Jeu> e) {return  e->getTitre()[0] ==  c; });
	cout << a->getTitre() << endl;

	
	//cout << a->getTitre();
	auto b = jeu0->chercherConcepteur([&](shared_ptr<Concepteur> c) {return  c->getNom() == "Yoshinori Kitase"; });
	//auto b = jeu0->chercherConcepteur("Yoshinori Kitase");
	cout << "Adresse du concepteur Yoshinori Kitase dans le premier jeu :  " << b << " Annee de naissance : " << b->getAnneeNaissance() << endl;

	auto e = jeu1->chercherConcepteur([&](shared_ptr<Concepteur> c) {return  c->getNom() == "Yoshinori Kitase"; });
	cout << "Adresse du concepteur Yoshinori Kitase dans le premier jeu :  " << e << " Annee de naissance : " << e->getAnneeNaissance() << endl;
	
	// 
	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}