#pragma once
#include "MidiEvent.h"
#include "GuitarEvent.h"

#include <vector>
#include "ChordDirections.h"

using namespace std;

class GuitarMidiEvent :
	public MidiEvent {
public:
	GuitarMidiEvent(UCHAR duration, UCHAR channel, vector<UCHAR> notes,
		ChordDirections chordDirection, UCHAR* velocity, Callback *callback);
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

