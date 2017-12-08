#pragma once
#include <vector>

using namespace std;

template<class T>
class Sequence {
public:
	Sequence();
	virtual ~Sequence();
	void deleteElement(vector<T*>::iterator iterator);
	vector<T*>::iterator getBegin();
	vector<T*>::iterator getEnd();
	UCHAR getSize();
	virtual vector<T*>::iterator addElement(T* pElement);
	virtual void insertElement(vector<T*>::iterator iterator, T* pElement);
protected:	
	vector<T*> elements;
};

