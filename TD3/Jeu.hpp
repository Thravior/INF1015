#pragma once
#include "Liste.hpp"
#include "Concepteur.hpp"
#include <string>
#include <memory>
#include <functional>
#include <iostream>

using namespace std;

class Jeu
{
public:
	//TODO: un constructeur par d�faut et un constructeur param�tr�.
	Jeu() = default;
	Jeu(const string& titre, const int anneeSortie, const string& developpeur,int nConcepteurs) {
		titre_ = titre;
		anneeSortie_ = anneeSortie;
		developpeur_ = developpeur;
		concepteurs_ = make_unique<Liste<Concepteur>>(nConcepteurs);
	}
	Jeu(const Jeu& jeu) {
		titre_ = jeu.getTitre();
		anneeSortie_ = jeu.getAnneeSortie();
		developpeur_ = jeu.getDeveloppeur();
	}


	const std::string& getTitre() const { return titre_; }
	void setTitre(const std::string& titre) { titre_ = titre; }

	unsigned getAnneeSortie() const { return anneeSortie_; }
	void setAnneeSortie(unsigned annee) { anneeSortie_ = annee; }

	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(const std::string& developpeur) { developpeur_ = developpeur; }

	//TODO: Pouvoir acc�der � la liste de concepteurs.
	Liste<Concepteur>* getConcepteurs() { return concepteurs_.get(); }
	//TODO: Votre m�thode pour trouver un concepteur selon un crit�re donn� par une lambda, en utilisant la m�thode de Liste.


private:
	std::string titre_;
	unsigned anneeSortie_;
	std::string developpeur_;
	//TODO: Attribut de la liste des concepteurs du jeu
	unique_ptr<Liste<Concepteur>> concepteurs_;

};