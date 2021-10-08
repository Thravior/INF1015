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
	//TODO: Constructeurs et surcharges d'op�rateurs
	Liste()=default;

	shared_ptr<T>& operator[] (int index) { return elements_[index]; }
	const shared_ptr<T>& operator[] (int index) const { return elements_[index]; }
	
	//TODO: M�thode pour ajouter un �l�ment � la liste
	void ajoutListe(shared_ptr<T>);


	// Pour size, on utilise le m�me nom que les accesseurs de la biblioth�que standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const         { return nElements_; }
	unsigned getCapacite() const  { return capacite_; }

	//TODO: M�thode pour changer la capacit� de la liste
	void augmenterCapacite(); 
	//TODO: M�thode pour trouver une �l�ment selon un crit�re (lambda).


private:
	unsigned int nElements_;
	unsigned int capacite_;
	//TODO: Attribut contenant les �l�ments de la liste.
	unique_ptr< shared_ptr<T>[] > elements_;

};

template <typename T>
void Liste<T>::ajoutListe(shared_ptr<T> ptr)
{
	if (nElements_ == capacite_) {
		augmenterCapacite();
	}
	elements_[nElements_] = move_shared(ptr);
	++nElements_;
}

template <typename T>
void Liste<T>::augmenterCapacite()
{
	capacite_ = std::max(capacite_ * 2, 1);
	auto ptr = make_unique<shared_ptr<T>[capacite_]>;
	for (auto i : range(size())) {
		ptr[i] = move(elements_[i]);
	}
	elements_ = move_unique(ptr);
}

