#pragma once
#include "Timer.h"
#include "Callback.h"
#include "Composition.h"
#include "MidiDevice.h"
#include "MidiComposition.h"

class MidiPlayer {
public:
	MidiPlayer(Timer* timer, Callback* stopCompositionCallback);
	~MidiPlayer();
	MidiComposition* play(MidiComposition* composition);
	BOOL pause();
	BOOL stop();
	BOOL resume();
	MidiDevice* getMidiDevice();

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
	Callback* stopCompositionCallback;

	void startComposition();
	void stopComposition();
};

