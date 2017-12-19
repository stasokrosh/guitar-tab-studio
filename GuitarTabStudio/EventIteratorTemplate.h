#pragma once
#include "EventIterator.h"
#include "EventFactory.h"
#include <vector>

using namespace std;

template<class T>
class EventIteratorTemplate : public EventIterator {
public:
	EventIteratorTemplate(vector<T*>* events, SHORT num, EventFactory* eventFactory) {
		this->events = events;
		this->num = num;
		this->eventFactory = eventFactory;
	}
	virtual Event* getEvent() {
		if (num == this->events->size()) {
			return NULL;
		} else {
			return this->events->at(this->num);
		}
	}
	T* getTemplateEvent() {
		if (num == this->events->size()) {
			return NULL;
		} else {
			return this->events->at(this->num);
		}
	}
	virtual void deleteEvent() {
		vector<T*>::iterator iterator = this->getIterator();
		this->events->erase(iterator);
		this->num--;
	}
	virtual void moveForward() {
		this->num++;
	}
	virtual void moveBackwards() {
		this->num--;
	}
	virtual void insertEvent(EventInfo eventInfo) {
		vector<T*>::iterator iterator = this->getIterator();
		iterator++;
		this->events->insert(iterator, reinterpret_cast<T*>(eventFactory->createEvent(eventInfo)));
	}
	virtual BOOL isLast() {
		return this->num == this->events->size() - 1;
	}
	virtual BOOL isFirst() {
		return this->num == 0;
	}
	virtual EventIterator* copy() {
		return new EventIteratorTemplate<T>(this->events, this->num, this->eventFactory);
	}
private:
	vector<T*>* events;
	SHORT num;
	EventFactory* eventFactory;
	
	typename vector<T*>::iterator getIterator() {
		SHORT i = 0;
		vector<T*>::iterator iterator = this->events->begin();
		while (i < this->num) {
			iterator++;
			i++;
		}
		return iterator;
	}
};

