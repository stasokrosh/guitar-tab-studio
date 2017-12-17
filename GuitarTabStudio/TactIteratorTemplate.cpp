#include "stdafx.h"
#include "TactIteratorTemplate.h"

template <class T>
TactIteratorTemplate<T>::TactIteratorTemplate(
	vector<T*>* tacts, typename vector<T*>::iterator iterator, TactFactory* tactFactory) {
	this->tacts = tacts;
	this->iterator = iterator;
	this->tactFactory = tactFactory;
}

template <class T>
TactIteratorTemplate<T>::~TactIteratorTemplate() {}

template<class T>
Tact * TactIteratorTemplate<T>::getTact() {
	if (iterator == this->tacts->end()) {
		return NULL;
	} else {
		return *iterator;
	}
}

template<class T>
T * TactIteratorTemplate<T>::getTemplateTact() {
	if (iterator == this->tacts->end()) {
		return NULL;
	} else {
		return *iterator;
	}
}

template<class T>
void TactIteratorTemplate<T>::deleteTact() {
	this->tacts->erase(iterator, iterator);
	this->iterator--;
}

template<class T>
void TactIteratorTemplate<T>::moveForward() {
	if (this->iterator != this->tacts->end()) {
		this->iterator++;
	}
}

template<class T>
void TactIteratorTemplate<T>::moveBackwards() {
	if (this->iterator != this->tacts->begin()) {
		this->iterator--;
	}
}

template<class T>
void TactIteratorTemplate<T>::insertTact(TactInfo * tactInfo) {
	this->tacts->insert(tactFactory->createTact(tactInfo));
}

template<class T>
BOOL TactIteratorTemplate<T>::isLast() {
	return this->getTact() == this->tacts->back();
}

template<class T>
BOOL TactIteratorTemplate<T>::isFirst() {
	return this->getTact() == this->tacts->front();
}

