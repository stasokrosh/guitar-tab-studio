#pragma once
#include "Event.h"
#include "PauseMidiEvent.h"

class PauseEvent : public Event{
public:
	PauseEvent(EventInfo eventInfo);
	virtual MidiEvent* getMidiEvent(UCHAR channel);
	virtual ViewComponent* getViewComponent(Scale scale) = 0;
	virtual BOOL isEmpty();
	~PauseEvent();
};

