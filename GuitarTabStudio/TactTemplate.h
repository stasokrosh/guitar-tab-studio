#pragma once
#include "Tact.h"
#include "EventIteratorTemplate.h"
#include "EventFactory.h"

template<class T>
class TactTemplate : public Tact {
public:
	TactTemplate(TactInfo* tactInfo, EventFactory* eventFactory);
	~TactTemplate();
	virtual EventIterator*  pushEvent(EventInfo eventInfo);
	virtual void popEvent();
	virtual T* getTemplateFront();
	virtual T* getTemplateBack();
	virtual Event* getFront();
	virtual Event* getBack();
	virtual UCHAR getSize();
	virtual EventIterator* getBegin();
	virtual EventIterator* getEnd();
	EventIteratorTemplate<T>* getTemplateBegin();
	EventIteratorTemplate<T>* getTemplateEnd();
private:
	vector<T*> events;
};

