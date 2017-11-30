#include "stdafx.h"
#include "Tact.h"

Tact::Tact(TactDuration* pTactDuration, BOOL repriseBegin, UCHAR repriseEnd) {
	this->pTactDuration = pTactDuration;
	this->repriseBegin = repriseBegin;
	this->repriseEnd = repriseEnd;
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
