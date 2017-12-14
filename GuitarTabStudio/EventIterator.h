#pragma once

#include "Event.h"

class EventIterator {
public:
	virtual Event* getEvent() = 0;
	virtual void deleteEvent() = 0;
	virtual void moveForward() = 0;
	virtual void moveBackwards() = 0;
	virtual void insertEvent(EventInfo eventInfo) = 0;
	virtual BOOL equal(EventIterator* eventIterator);
	virtual BOOL isLast() = 0;
	virtual BOOL isFirst() = 0;
	virtual USHORT getPosition() = 0;
};