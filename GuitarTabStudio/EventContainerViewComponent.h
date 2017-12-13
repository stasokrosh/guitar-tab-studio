#pragma once
#include "ViewComponent.h"
#include "EventViewComponent.h"

template<class T>
class EventContainerViewComponent : public ViewComponent {
public:
	EventContainerViewComponent(ViewInfo* viewInfo);
	~EventContainerViewComponent();
	virtual void resize(USHORT width, USHORT height);
	virtual void addEvents(vector<T*> events);
protected:
	vector<T*> events;
};

