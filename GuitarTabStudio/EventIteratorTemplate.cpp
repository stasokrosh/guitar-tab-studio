#include "stdafx.h"
#include "EventIteratorTemplate.h"

template<class T>
EventIteratorTemplate<T>::EventIteratorTemplate(vector<T*>* events, vector<T*>::iterator iterator,
	Tact* tact, EventFactory* eventFactory) {
	this->events = events;
	this->iterator = iterator;
	this->tact = tact;
	this->eventFactory = eventFactory;
}

template<class T>
EventIteratorTemplate<T>::~EventIteratorTemplate() {}

template<class T>
Event * EventIteratorTemplate<T>::getEvent() {
	if (iterator == this->events->end()) {
		return NULL;
	} else {
		return *iterator;
	}
}

template<class T>
T * EventIteratorTemplate<T>::getTemplateEvent() {
	if (iterator == this->events->end()) {
		return NULL;
	} else {
		return *iterator;
	}
}

template<class T>
void EventIteratorTemplate<T>::deleteEvent() {
	this->events->erase(iterator, iterator);
	this->iterator--;
}

template<class T>
void EventIteratorTemplate<T>::moveForward() {
	if (this->iterator != this->events->end()) {
		this->iterator++;
	}
}

template<class T>
void EventIteratorTemplate<T>::moveBackwards() {
	if (this->iterator != this->events->begin()) {
		this->iterator--;
	}
}

template<class T>
void EventIteratorTemplate<T>::insertEvent(EventInfo eventInfo) {
	this->events->insert(eventFactory->createEvent(eventInfo, this->tact));
}

template<class T>
BOOL EventIteratorTemplate<T>::isLast() {
	return this->getEvent() == this->events->back();
}

template<class T>
BOOL EventIteratorTemplate<T>::isFirst() {
	return this->getEvent() == this->events->front();
}

template<class T>
USHORT EventIteratorTemplate<T>::getPosition() {
	USHORT position = 0;
	vector<T*>::iterator iterator = this->events->begin();
	while (iterator != this->iterator) {
		position++;
		iterator++;
	}
	return position;
}
