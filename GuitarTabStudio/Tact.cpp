#include "stdafx.h"
#include "Tact.h"

Tact::Tact(TactDuration* pTactDuration, TactInfo* pTactInfo) {
	this->pTactDuration = pTactDuration;
	this->pTactInfo = pTactInfo;
}

Tact::~Tact() {}

TactValidity Tact::isValid() {
	USHORT tactAbsoluteBeatCount = ABSOLUTE_BEAT_COUNT_BASE * this->pTactDuration->beatCount / this->pTactDuration->beatType;
	USHORT notesAboluteBeatCount = 0;
	for (Event* pEvent : this->elements) {
		notesAboluteBeatCount += pEvent->getAbsoluteBeatCount();
	}
	return tactAbsoluteBeatCount == notesAboluteBeatCount ? VALID : tactAbsoluteBeatCount < notesAboluteBeatCount ? MORE : LESS;
}

void Tact::addMidiEventsToVector(UCHAR channel, vector<MidiEvent*>* vector) {	
	EventIterator iterator = this->getBegin();
	EventIterator endIterator = this->getEnd();
	while (iterator != endIterator) {
		vector->push_back((*iterator)->getMidiEvent(channel));
		iterator++;
	}
}

EventIterator Tact::addElement(Event * pElement) {
	pElement->tact = this;
	return Sequence::addElement(pElement);
}

void Tact::insertElement(EventIterator iterator, Event * pElement) {
	pElement->tact = this;
	Sequence::insertElement(iterator, pElement);
}

