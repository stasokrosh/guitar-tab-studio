#pragma once
#include "Core.h"

class Event {
public:	
	Event(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount);
	UCHAR getAbsoluteBeatCount();

	BeatType beatType;
	BeatTypeEx beatTypeEx;
	UCHAR dotCount;
};

