/*****************************************************************************************************************************************************
Auteur: Loup Olivier Gaven-Forest
Date: 10 Octobre
Fichier: mabTab.h
But: Créer une carte dynamique en utilisant un pointeur de pointeur
*****************************************************************************************************************************************************/

#pragma once
#include <cassert>
#include <iostream>
using namespace std;

template <class TYPE>
class map
{
protected:
	char *_name;			//pointeur sur le nom de la map
	TYPE  **_map;	//La map dynamique en ligne et colonne
	int	_nbLine, 		//nombre de ligne pour la matrice
		_nbCol;		//nombre de colonne pour la matrice
public:
	//Constructeurs/Destructeurs
	map();
	map(const char* name, int line, int col);
	map(const map& carte);
	~map();

	//Clears
	void clear();	//Apelle clearMartice() et clearNom()
	void clearMatrice();		//Vide le contenu de la carte
	void clearNom();		//Vide le contenu du nom de la carte

	//getteurs / setteurs
	int nbLine()const; 			//retourne le nb de ligne
	int nbCol()const; 			//retourne le nb de colonne
	const char* getName()const; 	  	//retourne le nom de la map
	void resize(int nbLine, int nbCol);//resize la matrice avec nouv dims
	TYPE& at(int posI, int posJ)const;	//retourne une référence à l’élément 
										//à la position i,j pour accéder ou modifier
	void setName(const char* name);  	//modifie le nom de la map

	//Lecture/Affichage
	void print(ostream& sortie)const;  	//print la matrice (sans le nom)
	void read(istream& entree);		//lit la matrice de la map ds le flux

	const map<TYPE>& operator=(const map<TYPE>& carte);
	TYPE* operator[](int line);
};
template <class TYPE>
ostream& operator<<(ostream& sortie, const map<TYPE>& map);
template <class TYPE>
istream& operator>>(istream& entree, map<TYPE>& x);

/***************************************************/
/********************Méthodes***********************/
/***************************************************/

//Constructeurs/Destructeurs
template <class TYPE>
map<TYPE>::map() {
	_name = nullptr;
	_map = nullptr;
	_nbLine = _nbCol = 0;
}

template <class TYPE>
map<TYPE>::map(const char* name, int line, int col) {
	assert(line >= 0 && col >= 0);
	_map = nullptr;
	_name = nullptr;
	_nbLine = line;
	_nbCol = col;

	if (_nbCol > 0 && _nbLine > 0) {
		_map = new TYPE*[_nbLine];
		for (int i = 0; i < _nbLine; i++)
			*(_map + i) = new TYPE[_nbCol];
	}

	//Appelle setName pour assigner le nom de la map
	setName(name);
}

template <class TYPE>
map<TYPE>::map(const map& carte) {
	_nbLine = carte._nbLine;
	_nbCol = carte._nbCol;
	_map = _name = nullptr;

	if (_nbLine != 0 && _nbCol != 0) {
		_map = new TYPE*[_nbLine];

		for (int i = 0; i < nbLine; i++)
			*(newMap + i) = new TYPE[nbCol];

		//On copie le contenu
		for (int i = 0; i < nbLine; i++) {
			for (int j = 0; j < nbCol; j++) {
				*(*(_map + i) + j) = *(*(carte._map + i) + j)
			}
		}
	}
}

template <class TYPE>
map<TYPE>::~map() {
	clear();
}


//Clears

//Apelle clearMartice() et clearNom()
template <class TYPE>
void map<TYPE>::clear() {
	clearMatrice();
	clearNom();
}


//Vide le contenu de la carte
template <class TYPE>
void map<TYPE>::clearMatrice() {
	for (int i = 0; i < _nbLine; i++) {
		delete[] * (_map + i);
	}
	delete[] _map;
	_map = nullptr;
	_nbLine = _nbCol = 0;
}


//Vide le contenu du nom de la carte
template <class TYPE>
void map<TYPE>::clearNom() {
	delete[] _name;
	_name = nullptr;
}


//getteurs / setteurs

//retourne le nb de ligne
template <class TYPE>
int map<TYPE>::nbLine()const {
	return _nbLine;
}

//retourne le nb de colonne
template <class TYPE>
int map<TYPE>::nbCol()const {
	return _nbCol;
}

//retourne le nom de la map
template <class TYPE>
const char* map<TYPE>::getName()const {
	if (_name == nullptr)
		return "/0";
	return _name;
}

//resize la matrice avec nouv dims
template <class TYPE>
void map<TYPE>::resize(int nbLine, int nbCol) {
	assert(nbLine >= 0 && nbCol >= 0);

	//On quitte si le resize est de la même taille
	if (nbLine == _nbLine && nbCol == _nbCol)
		return;

	//Si on veut resize à 0, on apelle clear à la place.
	if (nbLine == 0 && nbCol == 0)
	{
		clearMatrice();
		return;
	}

	TYPE **newMap = new TYPE*[nbLine];

	for (int i = 0; i < nbLine; i++)
		*(newMap + i) = new TYPE[nbCol];

	//On copie le contenu de la carte précédente dans la nouvelle 
	//seulement si le resize est plus petit
	for (int i = 0; i < _nbLine && i < nbLine; i++) {
		for (int j = 0; j < _nbCol && j < nbCol; j++) {
			*(*(newMap + i) + j) = *(*(_map + i) + j);
		}
	}

	//On affecte les nouvelles variables dans leur position
	clearMatrice();
	_nbLine = nbLine;
	_nbCol = nbCol;
	_map = newMap;
	newMap = nullptr;
}

//retourne une référence à l’élément à la position i,j pour accéder ou modifier
template <class TYPE>
TYPE& map<TYPE>::at(int posI, int posJ)const {
	assert(posI >= 0 && posI < _nbLine);
	assert(posJ >= 0 && posJ < _nbCol);
	return *(*(_map + posI) + posJ);
}

//modifie le nom de la map
template <class TYPE>
void map<TYPE>::setName(const char* name) {

	int nbChar = strlen(name);
	clearNom();

	//Si le nouveau nom est vide, on apelle clear
	if (nbChar != 0)
	{
		_name = new char[nbChar + 1];
		strcpy_s(_name, nbChar + 1, name);
	}
}


//Lecture/Affichage

//print la matrice (sans le nom)
template <class TYPE>
void map<TYPE>::print(ostream& sortie)const {
	for (int i = 0; i < _nbLine; i++) {
		for (int j = 0; j < _nbCol; j++) {
			sortie << *(*(_map + i) + j) << " ";
		}
		sortie << endl;
	}
	sortie << endl;
}

//lit la matrice de la map ds le flux
template <class TYPE>
void map<TYPE>::read(istream& entree) {
	assert(_map != nullptr);
	for (int i = 0; i < _nbLine; i++) {
		for (int j = 0; j < _nbCol; j++) {
			entree >> *(*(_map + i) + j);
		}
	}
}


//Opérateurs
template <class TYPE>
ostream& operator<<(ostream& sortie, const map<TYPE>& map) {
	map.print(sortie);
	return sortie;
}

template <class TYPE>
istream& operator>> (istream& entree, map<TYPE>& x) {
	map.read(entree);
	return entree;
}

template <class TYPE>
TYPE* map<TYPE>::operator[](int line) {
	assert(line >= 0 && line < _nbline);
	return *(_map + line);
}

template <class TYPE>
const map<TYPE>& map<TYPE>::operator=(const map<TYPE>& carte) {
	if (this == &carte)
		return *this;
	clear();
	_nbLine = carte._nbLine;
	_nbCol = carte._nbCol;

	if (_nbLine != 0 && _nbCol != 0) {
		_map = new TYPE*[_nbLine];

		for (int i = 0; i < nbLine; i++)
			*(newMap + i) = new TYPE[nbCol];

		//On copie le contenu
		for (int i = 0; i < nbLine; i++) {
			for (int j = 0; j < nbCol; j++) {
				*(*(newMap + i) + j) = *(*(_map + i) + j);
			}
		}
	}
	setNom(carte._name);
	return *this;
}