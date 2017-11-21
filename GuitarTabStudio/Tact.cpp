#include "stdafx.h"
#include "Tact.h"


Tact::Tact(TactDuration* pTactDuration, BOOL repriseBegin, UCHAR repriseEnd) {
	this->pTactDuration = pTactDuration;
	this->repriseBegin = repriseBegin;
	this->repriseEnd = repriseEnd;
}


Tact::~Tact() {}

vector<Event*>::iterator Tact::addEvent(Event * pEvent) {
	events.push_back(pEvent);
	return events.end();
}

void Tact::insertEvent(vector<Event*>::iterator iterator, Event * pEvent) {
	events.insert(iterator, pEvent);
}

void Tact::deleteEvent(vector<Event*>::iterator iterator) {
	events.erase(iterator, iterator);
}

vector<Event*>::iterator Tact::getBegin() {
	return events.begin();
}

vector<Event*>::iterator Tact::getEnd() {
	return events.end();
}

TactValidity Tact::isValid() {
	USHORT tactAbsoluteBeatCount = ABSOLUTE_BEAT_COUNT_BASE * this->pTactDuration->beatCount / this->pTactDuration->beatType;
	USHORT notesAboluteBeatCount = 0;
	for (Event* pEvent : events) {
		notesAboluteBeatCount += pEvent->getAbsoluteBeatCount();
	}
	return tactAbsoluteBeatCount == notesAboluteBeatCount ? VALID : tactAbsoluteBeatCount < notesAboluteBeatCount ? MORE : LESS;
}
