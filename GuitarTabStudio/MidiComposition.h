#pragma once
#include "Callback.h"
#include "MidiDevice.h"
#include "MidiTrack.h"

class MidiComposition : public Callback {
public:
	MidiComposition(MidiDevice* midiDevice,UCHAR tempo, MidiTrack** tracks, UCHAR trackCount);
	~MidiComposition();
	void initialize();
	void setCompositionEndCallback(Callback* compositionEndCallback);
	void call();
	UINT getTimerElapse();
private:
	static UINT getTimerElapseFromTempo(UCHAR tempo);
	BOOL compositionEnded();

	Callback* compositionEndCallback;
	UCHAR trackCount;
	MidiTrack** tracks;
	BOOL* trackEnded;
	MidiDevice* midiDevice;
	UINT timerElapse;
};

