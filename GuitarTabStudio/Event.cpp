#include "Event.h"

Event::Event(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount) {
	this->beatType = beatType;
	this->beatTypeEx = beatTypeEx;
	this->dotCount = dotCount;
}

UCHAR Event::getAbsoluteBeatCount() {
	UCHAR absoluteBeatCount = ABSOLUTE_BEAT_COUNT_BASE / (1 << this->beatType) * NORMAL / this->beatTypeEx;
	absoluteBeatCount = absoluteBeatCount * 2 - absoluteBeatCount / (1 << this->dotCount);
	return absoluteBeatCount;
}


