#include "stdafx.h"
#include "TactTemplate.h"

template<class T>
TactTemplate::TactTemplate(TactInfo* tactInfo, Track* track, EventFactory* eventFactory) : 
	Tact(tactInfo, track, eventFactory) {}

template<class T>
TactTemplate::~TactTemplate() {}

template<class T>
EventIterator* TactTemplate<T>::pushEvent(EventInfo eventInfo) {
	this->events.push_back(this->eventFactory->createEvent(eventInfo, this));
	return new EventIteratorTemplate<T>(&(this->events), this->events.end()--, this, this->eventFactory);
}

template<class T>
void TactTemplate<T>::popEvent() {
	this->events.pop_back();
}

template<class T>
T * TactTemplate<T>::getTemplateFront() {
	return this->events.front();
}

template<class T>
T * TactTemplate<T>::getTemplateBack() {
	return this->events.back();
}

template<class T>
Event * TactTemplate<T>::getFront() {
	return this->events.front();
}

template<class T>
Event * TactTemplate<T>::getBack() {
	return this->events.back();
}

template<class T>
UCHAR TactTemplate<T>::getSize() {
	return this->events.size();
}

template<class T>
EventIteratorTemplate<T> * TactTemplate<T>::getBegin() {
	return new EventIteratorTemplate<T>(&(this->events), this->events.begin(), this, this->eventFactory);
}

template<class T>
EventIteratorTemplate<T> * TactTemplate<T>::getEnd() {
	return new EventIteratorTemplate<T>(&(this->events), this->events.end(), this, this->eventFactory);
}

template<class T>
EventIterator * TactTemplate<T>::getEventIteratorByPosition(USHORT position) {
	vector<T*>::iterator = this->events.begin();
	USHORT i = 0;
	while (i < position) {
		i++;
		iterator++;
	}
	return new EventIteratorTemplate<T>(&(this->events), iterator, this, this->eventFactory);
}
