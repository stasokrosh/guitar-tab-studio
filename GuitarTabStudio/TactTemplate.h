#pragma once
#include "Tact.h"
#include "EventIteratorTemplate.h"

template<class T>
class TactTemplate : public Tact {
public:
	TactTemplate(TactInfo* tactInfo, Track* track, EventFactory* eventFactory);
	~TactTemplate();
	virtual void pushEvent(EventInfo eventInfo);
	virtual void popEvent();
	virtual T* getTemplateFront();
	virtual T* getTemplateBack();
	virtual Event* getFront();
	virtual Event* getBack();
	virtual UCHAR getSize();
	virtual EventIteratorTemplate<T>* getBegin();
	virtual EventIteratorTemplate<T>* getEnd();
private:
	vector<T> events;
};

