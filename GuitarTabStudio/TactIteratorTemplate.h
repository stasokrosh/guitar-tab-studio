#pragma once
#include "TactIterator.h"
#include "TactFactory.h"
#include <vector>

using namespace std;


template <class T>
class TactIteratorTemplate : public TactIterator {
public:
	TactIteratorTemplate(vector<T*>* tacts, typename vector<T*>::iterator iterator, TactFactory* tactFactory);
	~TactIteratorTemplate();
	virtual Tact* getTact();
	T* getTemplateTact();
	virtual void deleteTact();
	virtual void moveForward();
	virtual void moveBackwards();
	virtual void insertTact(TactInfo* tactInfo);
	virtual BOOL isLast();
	virtual BOOL isFirst();
private:
	vector<T*>* tacts;
	typename vector<T*>::iterator iterator;
	TactFactory* tactFactory;
};

