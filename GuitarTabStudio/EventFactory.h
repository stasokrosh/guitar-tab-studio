#pragma once
#include "Event.h"

class EventFactory {
public:
	virtual Event* createEvent(EventInfo eventInfo, Tact* tact) = 0;
};