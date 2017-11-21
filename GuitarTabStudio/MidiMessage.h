#pragma once
#include "Midi.h"

class MidiMessage {
public:
	MidiMessage(Message message);
	static MidiMessage startNoteMessage(UCHAR channel, UCHAR frequency, UCHAR velocity);
	static MidiMessage stopNoteMessage(UCHAR channel, UCHAR frequency);
	static MidiMessage changeInstrumentMessage(UCHAR channel, UCHAR instrument);
	ULONG getMessage();
private:
	Message message;
};

