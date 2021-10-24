/**
* Programme qui comprend la classe Liste et ses methodes. Cette classe agira
* differement selon le template choisi lors de son appel. On y retrouve aussi
* une fonction lamda. 
* \file   liste.hpp
* \author Laurie Bedard-Cote (2086165) et Mathias Gagnon (2115246)
* \date  24 octobre 2021
* \cree  6 octobre 2021
*/

#pragma once
#include <iostream>
#include <memory>
#include <cassert>
#include "gsl/span"
#include "cppitertools/range.hpp"

using namespace std;

template <typename T>
class Liste	
{
public:
	//TODO: Constructeurs et surcharges d'operateurs
	Liste() {
		nElements_ = 0;
		capacite_ = 0;
		elements_ = nullptr;
	}

	Liste(int taille) {
		nElements_ = 0;
		capacite_ = taille;
		elements_ = make_unique<shared_ptr<T>[]>(capacite_);
	}

	shared_ptr<T>& operator[] (int index) { return elements_[index]; }
	const shared_ptr<T>& operator[] (int index) const { return elements_[index]; }
	
	void operator+ (shared_ptr<T> element) { ajoutListe(element); }

	//TODO: Methode pour ajouter un element e la liste
	void ajoutListe(shared_ptr<T>);


	// Pour size, on utilise le meme nom que les accesseurs de la bibliotheque
	// standard, qui permet d'utiliser certaines fonctions de la bibliotheque 
	// sur cette classe.
	unsigned size() const         { return nElements_; }
	unsigned getCapacite() const  { return capacite_; }

	//TODO: Methode pour changer la capacite de la liste
	void augmenterCapacite(); 

	//TODO: Methode pour trouver une element selon un critere (lambda).
	shared_ptr<T> trouverCritere(const function<bool(shared_ptr<T>)>& critere){
		for (auto&& i : iter::range(nElements_))
		{
			if (critere(elements_[i])) {
				return elements_[i];
			}
		}
		return nullptr;
	}
	
private:
	unsigned int nElements_;
	unsigned int capacite_;
	//TODO: Attribut contenant les elements de la liste.
	unique_ptr< shared_ptr<T>[] > elements_;

};

template <typename T>
void Liste<T>::ajoutListe(shared_ptr<T> ptr)
{
	if (nElements_ == capacite_) {
		augmenterCapacite();
	}
	elements_[nElements_] = move(ptr);
	++nElements_;
}

template <typename T>
void Liste<T>::augmenterCapacite()
{
	capacite_ = max(capacite_ * 2, unsigned(1));
	
	auto ptr = make_unique<shared_ptr<T>[]>(capacite_);

	for (auto i : iter::range(nElements_) ) {
		ptr[i] = move(elements_[i]);
	}
	elements_ = move(ptr);
}