#pragma once
#include "Midi.h"
#include "MidiDevice.h"
#include "Callback.h"

class MidiEvent {
public:
	MidiEvent(UCHAR duration, UCHAR channel,Callback* changeNoteCallback);
	virtual BOOL play(MidiDevice* midiDevice);
	Callback* getChangeNoteCallback();
protected:
	UCHAR startDuration;
	UCHAR currentDuration;
	UCHAR channel;
	Callback* changeNoteCallback;
};

