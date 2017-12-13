#pragma once
#include "EventIterator.h"

template<class T>
class EventIteratorTemplate : public EventIterator {
public:
	EventIteratorTemplate(vector<T*>* events, vector<T*>::iterator iterator, Tact* tact, EventFactory* eventFactory);
	~EventIteratorTemplate();
	Event* getEvent();
	T* getTemplateEvent();
	void deleteEvent();
	void moveForward();
	void moveBackwards();
	void insertEvent(EventInfo eventInfo);
	BOOL isLast();
	BOOL isFirst();
private:
	vector<T*>* events;
	vector<T*>::iterator iterator;
	Tact* tact;
	EventFactory* eventFactory;
};

