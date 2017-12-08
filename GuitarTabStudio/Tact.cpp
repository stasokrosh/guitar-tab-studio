#include "stdafx.h"
#include "Tact.h"

Tact::Tact(TactInfo* tactInfo, Track* track) {
	this->tactInfo = tactInfo;
	this->track = track;
}

Tact::~Tact() {}

BOOL Tact::isValid() {
	USHORT tactAbsoluteBeatCount = ABSOLUTE_BEAT_COUNT_BASE * this->tactInfo->tactDuration->beatCount / this->tactInfo->tactDuration->beatType;
	USHORT notesAboluteBeatCount = 0;
	for (Event* pEvent : this->elements) {
		notesAboluteBeatCount += pEvent->getAbsoluteBeatCount();
	}
	return tactAbsoluteBeatCount == notesAboluteBeatCount;
}

void Tact::addMidiEventsToVector(UCHAR channel, UCHAR* velocity, vector<MidiEvent*>* vector) {	
	EventIterator iterator = this->getBegin();
	EventIterator endIterator = this->getEnd();
	while (iterator != endIterator) {
		vector->push_back((*iterator)->getMidiEvent(channel, velocity));
		iterator++;
	}
}

EventIterator Tact::addEvent(EventInfo eventInfo, EventFactory * eventFactory) {
	return Sequence::addElement(eventFactory->createEvent(eventInfo, this));
}

void Tact::insertEvent(EventIterator iterator, EventInfo eventInfo, EventFactory * eventFactory) {
	Sequence::insertElement(iterator, eventFactory->createEvent(eventInfo, this));
}

Track * Tact::getTrack() {
	return this->track;
}

TactInfo * Tact::getTactInfo() {
	return this->tactInfo;
}


