#pragma once
#include "Event.h"
#include "StringInstrument.h"

enum ChordDirections {
	UP,
	NONE,
	DOWN
};

class StringInstrumentChordEvent : public Event {
public:
	StringInstrumentChordEvent(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount,
		StringInstrument* stringInstrument, ChordDirections chordDirection);
	~StringInstrumentChordEvent();
	virtual MidiEvent* getMidiEvent(UCHAR channel);

	ChordDirections chordDirection;
	CHAR* notes;
protected:
	StringInstrument* stringInstrument;
};

