#pragma once
#include "Midi.h"

class MidiEvent {
public:
	MidiEvent(UCHAR duration, UCHAR channel);
	virtual BOOL play(MidiDevice midiDevice);
protected:
	UCHAR startDuration;
	UCHAR currentDuration;
	UCHAR channel;
};

