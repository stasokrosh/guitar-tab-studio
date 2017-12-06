#pragma once
#include "Event.h"
#include "PauseMidiEvent.h"

class PauseEvent : public Event{
public:
	PauseEvent(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount);
	virtual MidiEvent* getMidiEvent(UCHAR channel);
	virtual ViewComponent* getViewComponent(Scale scale) = 0;
	~PauseEvent();
};

