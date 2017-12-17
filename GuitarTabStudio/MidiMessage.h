#pragma once
#include "Midi.h"

class MidiMessage {
public:
	MidiMessage(Message message);
	MidiMessage();
	~MidiMessage();
	static MidiMessage StartNoteMessage(UCHAR channel, UCHAR frequency, UCHAR velocity);
	static MidiMessage StopNoteMessage(UCHAR channel, UCHAR frequency);
	static MidiMessage ChangeInstrumentMessage(UCHAR channel, UCHAR instrument);
	ULONG getMessage();
private:
	Message message;
};

