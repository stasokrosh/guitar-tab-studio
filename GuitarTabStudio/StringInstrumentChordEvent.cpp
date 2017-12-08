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

MidiEvent * StringInstrumentChordEvent::getMidiEvent(UCHAR channel, UCHAR* velocity) {
	vector<UCHAR> notes;
	for (int i = 0; i < this->stringInstrument->getStringCount; i++) {
		if (this->notes[i] >= 0) {
			notes.push_back(this->stringInstrument->getFrequency(this->notes[i], i));
		}
	}
	return new StringInstrumentChordMidiEvent(this->getAbsoluteBeatCount(), channel, this, notes ,this->chordDirection ,velocity);
}

BOOL StringInstrumentChordEvent::isEmpty() {
	for (int i = 0; i < this->stringInstrument->getStringCount; i++) {
		if (this->notes[i] >= 0) {
			return FALSE;
		}
	}
	return TRUE;
}
