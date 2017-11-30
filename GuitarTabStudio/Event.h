#pragma once
#include "Core.h"

class Event {
public:	
	Event(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount);
	UCHAR getAbsoluteBeatCount();
	virtual MidiEvent getMidiEvent(UCHAR channel) = 0;

	BeatType beatType;
	BeatTypeEx beatTypeEx;
	UCHAR dotCount;
};

