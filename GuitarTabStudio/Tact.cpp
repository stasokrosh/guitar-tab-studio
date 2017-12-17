#include "stdafx.h"
#include "Tact.h"

Tact::Tact(TactInfo* tactInfo, EventFactory* eventFactory) {
	this->tactInfo = tactInfo;
	this->eventFactory = eventFactory;
}

Tact::~Tact() {}

TactValidity Tact::isValid() {
	USHORT tactAbsoluteBeatCount = Tact::getTactAbsoluteBeatCount(this->tactInfo->tactDuration);
	USHORT notesAboluteBeatCount = 0;
	EventIterator* currentIterator = this->getBegin();
	EventIterator* endIterator = this->getBegin();
	while (!currentIterator->equal(endIterator)) {
		notesAboluteBeatCount += currentIterator->getEvent()->getAbsoluteBeatCount();
		currentIterator->moveForward();
	};
	delete currentIterator;
	delete endIterator;
	return tactAbsoluteBeatCount == notesAboluteBeatCount ? VALID : tactAbsoluteBeatCount > notesAboluteBeatCount ? LESS : MORE;
}


TactInfo * Tact::getTactInfo() {
	return this->tactInfo;
}

BOOL Tact::isEmpty() {
	EventIterator* currentIterator = this->getBegin();
	EventIterator* endIterator = this->getBegin();
	while (!currentIterator->equal(endIterator)) {
		if (!currentIterator->getEvent()->isPause() && !currentIterator->getEvent()->isEmpty()) {
			return FALSE;
		}
	}
	return TRUE;
}

USHORT Tact::getTactAbsoluteBeatCount(TactDuration * tactDuration) {
	return ABSOLUTE_BEAT_COUNT_BASE * tactDuration->beatCount / tactDuration->beatType;
}





