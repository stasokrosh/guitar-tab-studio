#include "stdafx.h"
#include "TactTemplate.h"

template<class T>
TactTemplate<T>::TactTemplate(TactInfo* tactInfo, EventFactory* eventFactory) : 
	Tact(tactInfo, eventFactory) {}

template<class T>
TactTemplate<T>::~TactTemplate() {}

template<class T>
EventIterator* TactTemplate<T>::pushEvent(EventInfo eventInfo) {
	this->events.push_back(this->eventFactory->createEvent(eventInfo, this));
	return new EventIteratorTemplate<T>(&(this->events), this->events.end()--, this->eventFactory);
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
EventIterator* TactTemplate<T>::getBegin() {
	return new EventIteratorTemplate<T>(&(this->events), this->events.begin(), this->eventFactory);
}

template<class T>
EventIterator* TactTemplate<T>::getEnd() {
	return new EventIteratorTemplate<T>(&(this->events), this->events.end(), this->eventFactory);
}

template <class T>
EventIteratorTemplate<T>* TactTemplate<T>::getTemplateBegin() {
	return new EventIteratorTemplate<T>(&(this->events), this->events.begin(), this->eventFactory);
}

template <class T>
EventIteratorTemplate<T>* TactTemplate<T>::getTemplateEnd() {
	return new EventIteratorTemplate<T>(&(this->events), this->events.begin(), this->eventFactory);
}


