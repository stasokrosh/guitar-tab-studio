#pragma once
#include "Tact.h"
#include "EventIteratorTemplate.h"

template<class T>
class TactTemplate : public Tact {
public:
	TactTemplate(TactInfo* tactInfo, Track* track, EventFactory* eventFactory);
	~TactTemplate();
	virtual EventIterator*  pushEvent(EventInfo eventInfo);
	virtual void popEvent();
	virtual T* getTemplateFront();
	virtual T* getTemplateBack();
	virtual Event* getFront();
	virtual Event* getBack();
	virtual UCHAR getSize();
	virtual EventIteratorTemplate<T>* getBegin();
	virtual EventIteratorTemplate<T>* getEnd();
	virtual EventIterator* getEventIteratorByPosition(USHORT position);
private:
	vector<T> events;
};

