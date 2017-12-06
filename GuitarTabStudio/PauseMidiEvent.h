#pragma once
#include "MidiEvent.h"
class PauseMidiEvent : public MidiEvent {
public:
	PauseMidiEvent(UCHAR duration, UCHAR channel, Event* event);
	~PauseMidiEvent();
};

