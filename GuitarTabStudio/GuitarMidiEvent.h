#pragma once
#include "MidiEvent.h"
#include "GuitarEvent.h"

#include <vector>

using namespace std;

class GuitarMidiEvent :
	public MidiEvent {
public:
	GuitarMidiEvent(UCHAR duration, UCHAR channel,GuitarEvent * event,
		vector<UCHAR> notes, ChordDirections chordDirection, UCHAR* velocity);
	~GuitarMidiEvent();
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
