#include "Event.h"

Event::Event(EventInfo eventInfo, Tact* tact) {
	this->eventInfo = eventInfo;
	this->tact = tact;
}

UCHAR Event::getAbsoluteBeatCount() {
	UCHAR absoluteBeatCount = ABSOLUTE_BEAT_COUNT_BASE / (1 << this->eventInfo.beatType) * NORMAL / this->eventInfo.beatTypeEx;
	absoluteBeatCount = absoluteBeatCount * 2 - absoluteBeatCount / (1 << this->eventInfo.dotCount);
	return absoluteBeatCount;
}

Tact * Event::getTact() {
	return this->tact;
}

EventInfo * Event::getEventInfo() {
	return &(this->eventInfo);
}


