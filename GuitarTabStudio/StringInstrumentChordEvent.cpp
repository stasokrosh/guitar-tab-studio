#include "stdafx.h"
#include "StringInstrumentChordEvent.h"


StringInstrumentChordEvent::StringInstrumentChordEvent(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount,
	StringInstrument* stringInstrument, ChordDirections chordDirection) : Event(beatType, beatTypeEx, dotCount) {
	this->stringInstrument = stringInstrument;
	this->chordDirection = chordDirection;
	this->notes = new CHAR[stringInstrument->getStringCount] { -1 };
}


StringInstrumentChordEvent::~StringInstrumentChordEvent() {
	delete[] this->notes;
}

MidiEvent * StringInstrumentChordEvent::getMidiEvent(UCHAR channel) {
	return ;
}
