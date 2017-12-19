#include "stdafx.h"
#include "Tact.h"

Tact::Tact(TactInfo* tactInfo, EventFactory* eventFactory) {
	this->tactInfo = tactInfo;
	this->eventFactory = eventFactory;
}

Tact::~Tact() {
}

TactValidity Tact::isValid() {
	SHORT tactAbsoluteBeatCount = Tact::getTactAbsoluteBeatCount(this->tactInfo->tactDuration);
	SHORT notesAboluteBeatCount = 0;
	EventIterator* currentIterator = this->getBegin();
	EventIterator* endIterator = this->getEnd();
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
	EventIterator* endIterator = this->getEnd();
	while (!currentIterator->equal(endIterator)) {
		if (!currentIterator->getEvent()->isPause()) {
			return FALSE;
		}
		currentIterator->moveForward();
	}
	return TRUE;
}

SHORT Tact::getTactAbsoluteBeatCount(TactDuration * tactDuration) {
	return ABSOLUTE_BEAT_COUNT_BASE * tactDuration->beatCount / tactDuration->beatType;
}





