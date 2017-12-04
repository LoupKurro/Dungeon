/*******************************************************************************
* Auteur:	Marie-Noelle Dussault
* Date:		18/11/2017
* Fichier:	liste.hpp
* But:		coder la version explicite circulaire à double pointeurs de la liste
********************************************************************************/
#pragma once
#include <assert.h>
template <typename TYPE> class list;

//CLASSE CELLULE
template <typename TYPE>
class cellule
{
	friend class list<TYPE>;	//la seule classe ayant accès à la 
								//représentation de la cellule
	TYPE element;				//Contenu de la cellule
	cellule <TYPE> *next;		//Pointeur vers la cellule suivante 
	cellule <TYPE> *previous;	//Pointeur vers la cellule precedente

	cellule(const TYPE &e, cellule<TYPE> *n = nullptr, cellule<TYPE> *p = nullptr)
	{
		element = e;
		next = n;
		previous = p;
	}
};

template <typename TYPE>
class list
{
private:
	cellule <TYPE> *_first;		//Adresse du premier élément 

	list(const list<TYPE> &l);		//Copieur désactivé
public:
	class iterator
	{
		friend class list<TYPE>;
	private:
		cellule<TYPE>* 	_current;		//adresse de la cellule
		const list<TYPE>* _list;		//adresse de la liste
	public:
		iterator();					//constructeurs
		~iterator();				//destructeur

		const iterator& operator=(const iterator& I);//pour j=i

		bool operator==(const iterator& I)const; //pour if(j==i)
		bool operator!=(const iterator& I)const; //pour if(j!=i)

		iterator operator++();			//i++
		const iterator& operator++(int i);		//++i

		iterator operator--();			//i--
		const iterator& operator--(int i);		//--i

		TYPE& operator*();					//accès à un élément
		const TYPE& operator*()const;		//idem, en mode const

	};

	list(void);								//constructeur de liste
	~list(void);

	void clear();							//vider la liste
	bool empty()const;						//si la liste est vide

	iterator begin()const;					//return premier
	iterator end()const;					//return NULL

	iterator insert(iterator I, const TYPE& e);	//inserer un element a position de it
	iterator erase(iterator I);					//retirer un element a position de it
	iterator erase(iterator first, iterator last);//retirer les element first a last

	TYPE& operator[](iterator I);		//pas ds la STL
	const TYPE& operator[](iterator I)const;

	//chercher dans la liste l’élément reçu en paramètre et à partir de l’itérateur
	//reçu pour la version 2 la méthode  retourne un iterator sur l’element trouvé
	//s’il est innexistant, l’iterator est à la fin 
	iterator operator()(const TYPE& ele)const;
	iterator operator()(const TYPE& ele, iterator I)const;

	const list<TYPE>& operator=(const list<TYPE>& l);	//pour l1=l2
};

//Méthodes de l'itérateur

//constructeur d'iterateur de liste
template<typename TYPE>
list<TYPE>::iterator::iterator()
{
	_list = nullptr;
	_current = nullptr;
}

//destructeur d'itérateur
template<typename TYPE>
list<TYPE>::iterator::~iterator()
{
	_list = nullptr;
	_current = nullptr;
}

//pour j=i
template<typename TYPE>
const typename list<TYPE>::iterator & list<TYPE>::iterator::operator=(const
	iterator & I)
{
	_current = I._current;
	_list = I._list;

	return *this;
}

//pour if(j==i)
template<typename TYPE>
bool list<TYPE>::iterator::operator==(const iterator & I) const
{
	assert(_list == I._list);
	return _current == I._current;

}

//pour if(j!=i)
template<typename TYPE>
bool list<TYPE>::iterator::operator!=(const iterator & I) const
{
	assert(_list == I._list);
	return _current != I._current;
}

//++i
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator++()
{
	assert(_list != nullptr);
	assert(_current != nullptr);
	assert(!_list->empty());

	if (_current->next == _list->_first)
		_current = nullptr;
	else
		_current = _current->next;

	return *this;
}
//i++
template<typename TYPE>
const typename list<TYPE>::iterator & list<TYPE>::iterator::operator++(int i)
{
	iterator it(*this);
	operator ++();
	return it;
}

//--i
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator--()
{
	assert(_list != nullptr);
	assert(!_list->empty());
	assert(_current != _list->_first);

	if (_current == nullptr)
		_current = _list->_first->previous;
	else
		_current = _current->previous;

	return *this;
}

//i--
template<typename TYPE>
const typename list<TYPE>::iterator & list<TYPE>::iterator::operator--(int i)
{
	iterator it(*this);
	operator--();
	return it;
}

//accès à un élément 
template<typename TYPE>
TYPE & list<TYPE>::iterator::operator*()
{
	assert(_list != nullptr);
	assert(!_list->empty());
	assert(_current != nullptr);
	return _current->element;

}

//accès à un élément en mode constant
template<typename TYPE>
const TYPE & list<TYPE>::iterator::operator*() const
{
	return operator*();
}

//Méthodes de liste
//constructeur de liste
template<typename TYPE>
list<TYPE>::list(void)
{
	_first = nullptr;
}

//destructeur de liste
template<typename TYPE>
list<TYPE>::~list(void)
{
	clear();
}

//vider la liste
template<typename TYPE>
void list<TYPE>::clear()
{
	erase(begin(), end());
}

//si la liste est vide
template<typename TYPE>
bool list<TYPE>::empty() const
{
	return _first == nullptr;
}

//return premier
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::begin() const
{
	list<TYPE>::iterator it;	//Itérateur sur le début (1ere cellule)

	it._current = _first;
	it._list = this;

	return it;
}

//return NULL
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::end() const
{
	list<TYPE>::iterator it;	//Itérateur sur la fin

	it._current = nullptr;
	it._list = this;

	return it;
}

//inserer un element a position de it
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::insert(iterator I, const TYPE & e)
{
	assert(I._list == this);

	if (_first == nullptr)
		_first->next = _first->previous = I._current = _first = new cellule<TYPE>(e);

	else if (I._current == nullptr)
		I._current = _first->previous = _first->previous->next = new cellule<TYPE>
		(e, _first, _first->previous);

	else {
		I._current = I._current->previous = I._current->previous->next = new
			cellule<TYPE>(e, I._current, I._current->previous);

		if (_first = I._current->next)
			_first = I._current;
	}

	return I;
}

//retirer un element a position de it
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator I)
{
	assert(I._current != nullptr);
	assert(I._list == this);
	assert(!empty());

	cellule<TYPE> *trash = I._current;

	if (I._current == I._current->previous)	//si il reste une seule cellule
		_first = I._current = nullptr;		//on met current et first a null
	else {
		trash->next->previous = trash->previous;
		I._current->previous->next = I._current->next;

		if (trash == _first)
			_first = trash->next;

		if (I._current == _first->previous)
			I._current = trash->previous;
		else
			I._current = trash->next;
	}

	delete trash;

	return I;
}

//retirer les elements first jusqu'a last
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator first, iterator last)
{
	assert(last._list == this);	//first est vérifier par erase(first)

	while (first != last) {
		first = erase(first);
	}
	return first;
}

template<typename TYPE>
TYPE & list<TYPE>::operator[](iterator I)
{
	assert(I._list == this);
	return *I;
}

template<typename TYPE>
const TYPE & list<TYPE>::operator[](iterator I) const
{
	assert(I._list == this);
	return *I;
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE & ele) const
{
	return operator()(ele, begin());
}

template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE & ele,
	iterator I) const
{
	assert(I._list == this);

	while (I != end()) {
		if (*I == ele)
			return I;

		I++;
	}
	return I;
}

//pour l1=l2
template<typename TYPE>
const list<TYPE>& list<TYPE>::operator=(const list<TYPE>& l)
{
	if (this == &l)
		return *this;

	clear();
	list<TYPE>::iterator itl = l.begin();

	while (itl != l.end()) {
		insert(end(), *itl);
		itl++;
	}

	return *this;
}

