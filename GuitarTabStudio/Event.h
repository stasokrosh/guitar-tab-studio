#pragma once
#include "Core.h"
#include "Tact.h"

#include "ViewComponent.h"
#include "View.h"

#include "MidiEvent.h"


class Event {
public:	
	Event(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount);
	UCHAR getAbsoluteBeatCount();
	virtual MidiEvent* getMidiEvent(UCHAR channel) = 0;
	virtual ViewComponent* getViewComponent(Scale scale) = 0;

	Tact* tact;
	BeatType beatType;
	BeatTypeEx beatTypeEx;
	UCHAR dotCount;
};

