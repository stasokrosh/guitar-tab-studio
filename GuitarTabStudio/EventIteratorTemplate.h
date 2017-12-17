#pragma once
#include "EventIterator.h"
#include "EventFactory.h"
#include <vector>

using namespace std;

template<class T>
class EventIteratorTemplate : public EventIterator {
public:
	EventIteratorTemplate(vector<T*>* events, typename vector<T*>::iterator iterator, EventFactory* eventFactory);
	~EventIteratorTemplate();
	virtual Event* getEvent();
	T* getTemplateEvent();
	virtual void deleteEvent();
	virtual void moveForward();
	virtual void moveBackwards();
	virtual void insertEvent(EventInfo eventInfo);
	virtual BOOL isLast();
	virtual BOOL isFirst();
	virtual EventIterator* copy();
private:
	vector<T*>* events;
	typename vector<T*>::iterator iterator;
	EventFactory* eventFactory;
};

