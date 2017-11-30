#pragma once
#include "Util.h"
#include "Composition.h"
#include "MidiDevice.h"
#include "MidiComposition.h"

class MidiPlayer {
public:
	MidiPlayer(Timer* timer, Callback* changeNoteCallback);
	~MidiPlayer();
	MidiComposition* play(Composition* composition);
	BOOL pause();
	BOOL stop();
	BOOL resume();
private:
	MidiComposition* midiComposition;
	MidiDevice midiDevice;
	Timer* timer;
	Callback* changeNoteCallback;
	void startComposition();
	void stopComposition();
};

