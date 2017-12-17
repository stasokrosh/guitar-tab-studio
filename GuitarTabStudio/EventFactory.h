#pragma once
#include "Common.h"
#include "Event.h"

class EventFactory {
public:
	virtual Event* createEvent(EventInfo eventInfo) = 0;
};