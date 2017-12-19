#pragma once
#include "Tact.h"
#include "EventIteratorTemplate.h"
#include "EventFactory.h"

template<class T>
class TactTemplate : public Tact {
public:
	TactTemplate(TactInfo* tactInfo, EventFactory* eventFactory) : Tact(tactInfo, eventFactory) {
	}
	virtual ~TactTemplate() { 
		this->events.clear();
	}
	virtual EventIterator*  pushEvent(EventInfo eventInfo) {
		this->events.push_back(reinterpret_cast<T*>(this->eventFactory->createEvent(eventInfo)));
		return new EventIteratorTemplate<T>(&(this->events), this->events.size() - 1, this->eventFactory);
	}
	virtual void popEvent() {
		this->events.pop_back();
	}
	virtual T* getTemplateFront() {
		return this->events.front();
	}
	virtual T* getTemplateBack() {
		return this->events.back();
	}
	virtual Event* getFront() {
		return this->events.front();
	}
	virtual Event* getBack() {
		return this->events.back();
	}
	virtual UCHAR getSize() {
		return this->events.size();
	}
	virtual EventIterator* getBegin() {
		return new EventIteratorTemplate<T>(&(this->events), 0 , this->eventFactory);
	}
	virtual EventIterator* getEnd() {
		return new EventIteratorTemplate<T>(&(this->events), this->events.size(), this->eventFactory);
	}
	EventIteratorTemplate<T>* getTemplateBegin() {
		return new EventIteratorTemplate<T>(&(this->events), 0 , this->eventFactory);
	}
	EventIteratorTemplate<T>* getTemplateEnd() {
		return new EventIteratorTemplate<T>(&(this->events), this->events.size(), this->eventFactory);
	}
private:
	vector<T*> events;
};

