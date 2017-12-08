#pragma once
#include "Core.h"
#include "Event.h"

class EventFactory {
public:
	virtual Event* createEvent(EventInfo event, Tact* tact) = 0;
};