#pragma once
#include "Midi.h"
#include "Event.h"

class MidiEvent {
public:
	MidiEvent(UCHAR duration, UCHAR channel, Event* event);
	Event* getEvent();
	virtual BOOL play(MidiDevice* midiDevice);
protected:
	UCHAR startDuration;
	UCHAR currentDuration;
	UCHAR channel;
	Event* event;
};

