#pragma once
#include "TactIterator.h"

template <class T>
class TactIteratorTemplate : public TactIterator {
public:
	TactIteratorTemplate(vector<T*>* tacts, vector<T*>::iterator iterator, Track* track, TactFactory* tactFactory);
	~TactIteratorTemplate();
	virtual Tact* getTact();
	T* getTemplateTact();
	virtual void deleteTact();
	virtual void moveForward();
	virtual void moveBackwards();
	virtual void insertTact(TactInfo* tactInfo);
	virtual BOOL isLast();
	virtual BOOL isFirst();
	virtual USHORT getPosition();
private:
	vector<T*>* tacts;
	vector<T*>::iterator iterator;
	Track* track;
	TactFactory* tactFactory;
};

