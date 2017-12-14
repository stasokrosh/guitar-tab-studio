#pragma once
#include "EventIterator.h"

template<class T>
class EventIteratorTemplate : public EventIterator {
public:
	EventIteratorTemplate(vector<T*>* events, vector<T*>::iterator iterator, Tact* tact, EventFactory* eventFactory);
	~EventIteratorTemplate();
	virtual Event* getEvent();
	T* getTemplateEvent();
	virtual void deleteEvent();
	virtual void moveForward();
	virtual void moveBackwards();
	virtual void insertEvent(EventInfo eventInfo);
	virtual BOOL isLast();
	virtual BOOL isFirst();
	virtual USHORT getPosition();
private:
	vector<T*>* events;
	vector<T*>::iterator iterator;
	Tact* tact;
	EventFactory* eventFactory;
};

