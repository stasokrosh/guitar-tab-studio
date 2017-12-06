#pragma once
#include "Timer.h"
#include "Callback.h"
#include "Composition.h"
#include "MidiDevice.h"
#include "MidiComposition.h"

class MidiPlayer {
public:
	MidiPlayer(Timer* timer, Callback* changeNoteCallback);
	~MidiPlayer();
	MidiComposition* play(Composition* composition,Track* selectedTrack,TactInfo* selectedTact);
	BOOL pause();
	BOOL stop();
	BOOL resume();

	class CompositionEndCallback : public Callback {
	public:
		CompositionEndCallback(MidiPlayer* midiPlayer);
		void call();
	private:
		MidiPlayer* midiPlayer;
	};
private:
	MidiComposition* midiComposition;
	MidiDevice midiDevice;
	Timer* timer;
	Callback* changeNoteCallback;
	void startComposition();
	void stopComposition();
};

