#pragma once
#include <iostream>
#include <memory>
#include <cassert>
#include "gsl/span"
#include "cppitertools/range.hpp"

template <typename T>
class Liste
{
public:
	//TODO: Constructeurs et surcharges d'opérateurs

	//TODO: Méthode pour ajouter un élément à la liste
	void ajoutListe(shared_ptr<T>);


	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const         { return nElements_; }
	unsigned getCapacite() const  { return capacite_; }

	//TODO: Méthode pour changer la capacité de la liste
	void augmenterCapacite()	  { capacite_ = std::max(capacite_ * 2,1); }
	//TODO: Méthode pour trouver une élément selon un critère (lambda).
	
private:
	unsigned int nElements_;
	unsigned int capacite_;
	//TODO: Attribut contenant les éléments de la liste.
	unique_ptr< shared_ptr<T>[] > elements_;

	void creerListeAgrandie();
};

template <typename T>
void Liste<T>::ajoutListe(shared_ptr<T> ptr)
{
	if (nElements_ == capacite_) {
		augmenterCapacite();
		creerListeAgrandie();
	}
	elements_[nElements_] = move_shared(ptr);
	++nElements_;
}

template <typename T>
void Liste<T>::creerListeAgrandie()
{
	auto ptr = make_unique<shared_ptr<T>[]>(capacite_);
	for (auto i : range(size())) {
		ptr[i] = move(elements_[i]);
	}
	elements_ = move_unique(ptr);
}