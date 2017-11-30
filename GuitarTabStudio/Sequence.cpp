#include "stdafx.h"
#include "Sequence.h"

template<class T>
Sequence<T>::Sequence() {}

template<class T>
Sequence<T>::~Sequence() {
	for (T* pElement : this->elements) {
		delete pElement;
	}
}

template<class T>
vector<T*>::iterator Sequence<T>::addElement(T * pElement) {
	this->elements.push_back(pElement);
	return this->elements.end();
}

template<class T>
void Sequence<T>::insertElement(vector<T*>::iterator iterator, T * pElement) {
	this->elements.insert(iterator, pElement);
}

template<class T>
void Sequence<T>::deleteElement(vector<T*>::iterator iterator) {
	delete *iterator;
	this->elements.erase(iterator, iterator);
}

template<class T>
vector<T*>::iterator Sequence<T>::getBegin() {
	return this->elements.begin();
}

template<class T>
vector<T*>::iterator Sequence<T>::getEnd() {
	return this->elements.end();
}
