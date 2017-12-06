#pragma once
#include "MidiEvent.h"
#include "StringInstrumentChordEvent.h"

#include <vector>

using namespace std;

class StringInstrumentChordMidiEvent :
	public MidiEvent {
public:
	StringInstrumentChordMidiEvent(UCHAR duration, UCHAR channel,StringInstrumentChordEvent * event,
		vector<UCHAR> notes, ChordDirections chordDirection, UCHAR* velocity);
	~StringInstrumentChordMidiEvent();
	virtual BOOL play(MidiDevice* midiDevice);
private:
	UCHAR getCurrentDelta();
	vector<UCHAR> notes;
	ChordDirections chordDirection;
	UCHAR* velocity;

	void play(UCHAR noteNum, MidiDevice* midiDevice);
	void stop(UCHAR noteNum, MidiDevice* midiDevice);
	void playAll(MidiDevice* midiDevice);
	void stopAll(MidiDevice* midiDevice);
};

