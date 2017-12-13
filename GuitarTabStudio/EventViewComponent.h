#pragma once
#include "ViewComponent.h"
#include "Event.h"

class EventViewComponent :
	public ViewComponent {
public:
	EventViewComponent(ViewInfo* viewInfo, Callback* clickCallback, Event* event);
	~EventViewComponent();
	Event* getEvent();
private:
	Event* event;
};

