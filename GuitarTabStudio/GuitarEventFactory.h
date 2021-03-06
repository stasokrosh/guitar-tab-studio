#pragma once
#include "EventFactory.h"
#include "GuitarEvent.h"

class GuitarEventFactory :
	public EventFactory {
public:
	GuitarEventFactory(Guitar* guitar);
	~GuitarEventFactory();
	virtual Event* createEvent(EventInfo eventInfo);
private:
	Guitar* guitar;
};

