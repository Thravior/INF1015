/**
* Programme qui comprend la classe Jeu et ses differentes methodes. On y 
* retrouve aussi une fonction lambda.
* \file   Jeu.hpp
* \author Laurie Bedard-Cote (2086165) et Mathias Gagnon (2115246)
* \date  24 octobre 2021
* \cree  6 octobre 2021
*/
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
	//TODO: un constructeur par défaut et un constructeur paramétré.
	Jeu() = default;
	Jeu(const string& titre, const int anneeSortie, const string& developpeur,
		int nConcepteurs) 
	{
		titre_		 = titre;
		anneeSortie_ = anneeSortie;
		developpeur_ = developpeur;
		concepteurs_ = make_unique<Liste<Concepteur>>(nConcepteurs);
	}

	Jeu(const Jeu& jeu) 
	{
		titre_		 = jeu.getTitre();
		anneeSortie_ = jeu.getAnneeSortie();
		developpeur_ = jeu.getDeveloppeur();
		concepteurs_ = make_unique<Liste<Concepteur>>(jeu.concepteurs_.get()->size());
		
		for (auto i : iter::range(jeu.concepteurs_.get()->size())) {
			concepteurs_.get()->ajoutListe(jeu.concepteurs_.get()->operator[](i));
		}
	}
	
	
	const std::string& getTitre() const			{ return titre_; }
	void	 setTitre(const std::string& titre) { titre_ = titre; }

	unsigned getAnneeSortie() const				{ return anneeSortie_; }
	void	 setAnneeSortie(unsigned annee) { anneeSortie_ = annee; }

	const std::string& getDeveloppeur() const	{ return developpeur_; }
	void	 setDeveloppeur(const std::string& developpeur) { developpeur_ = developpeur; }

	//TODO: Pouvoir accéder à la liste de concepteurs.
	Liste<Concepteur>* getConcepteurs()			{ return concepteurs_.get(); }

	//TODO: Votre méthode pour trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.
	shared_ptr<Concepteur> chercherConcepteur(const function<bool(shared_ptr<Concepteur>)>& critere){
		return concepteurs_->trouverCritere(critere);
	}

private:
	std::string titre_;
	unsigned	anneeSortie_;
	std::string developpeur_;

	//TODO: Attribut de la liste des concepteurs du jeu
	unique_ptr<Liste<Concepteur>> concepteurs_;

};

