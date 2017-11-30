#pragma once
#include "Core.h"

using namespace std;

template<class T>
class Sequence {
public:
	Sequence();
	virtual ~Sequence();
	virtual vector<T*>::iterator addElement(T* pElement);
	virtual void insertElement(vector<T*>::iterator iterator, T* pElement);
	void deleteElement(vector<T*>::iterator iterator);
	vector<T*>::iterator getBegin();
	vector<T*>::iterator getEnd();
protected:
	vector<T*> elements;
};

