// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include "cppitertools/range.hpp"
using namespace std;

#pragma region "Fonctions de lecture de base"
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

std::shared_ptr<Concepteur> chercherConcepteur(Liste<Jeu>& listeJeux, std::string nom)
{
	//TODO: Compléter la fonction (équivalent de trouverDesigner du TD2).
	for (auto i : iter::range(listeJeux.size())) {
		for (auto j : iter::range(listeJeux[i]->getConcepteurs()->size())) {
			if (listeJeux[i]->getConcepteurs()->operator[](j)->getNom() == nom) {
				return listeJeux[i]->getConcepteurs()->operator[](j);
			}
		}
	}
	return nullptr;
}

shared_ptr<Concepteur> lireConcepteur(Liste<Jeu>& lj, istream& f)
{
	string nom              = lireString(f);
	unsigned anneeNaissance = lireUint16(f);
	string pays             = lireString(f);

	//TODO: Compléter la fonction (équivalent de lireDesigner du TD2).
	shared_ptr<Concepteur> ptrC = chercherConcepteur(lj, nom);
	if (ptrC == nullptr) {
		ptrC = make_shared<Concepteur>(nom, anneeNaissance, pays);
	}
	//cout << "C: " << nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return ptrC;
}

shared_ptr<Jeu> lireJeu(istream& f, Liste<Jeu>& lj)
{
	string titre          = lireString(f);
	unsigned anneeSortie  = lireUint16(f);
	string developpeur    = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	//TODO: Compléter la fonction (équivalent de lireJeu du TD2).
	auto ptrJeu = make_shared<Jeu>(titre, anneeSortie, developpeur, nConcepteurs);

	for (unsigned int i = 0; i < nConcepteurs; i++)
		ptrJeu->getConcepteurs()->ajoutListe( lireConcepteur(lj, f));

	//cout << "J: " << titre << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return ptrJeu;
}

Liste<Jeu> creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	//TODO: Compléter la fonction.
	Liste<Jeu> listeJeux;
	for ([[maybe_unused]] int i : iter::range(nElements))
		listeJeux + lireJeu(f, listeJeux);

	return listeJeux;
}
