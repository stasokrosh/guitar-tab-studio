#pragma once
#include "Callback.h"
#include "MidiDevice.h"
#include "MidiTrack.h"
#include "Track.h"

class MidiComposition : public Callback {
public:
	MidiComposition(MidiDevice* midiDevice,UCHAR tempo,MidiTrack** tracks, UCHAR trackCount, MidiTrack* selectedTrack);
	~MidiComposition();
	void initialize();
	void setChangeNoteCallBack(Callback* changeNoteCallBack);
	void setCompositionEndCallback(Callback* compositionEndCallback);
	void selectTrack(Track* track);
	void call();
	UINT getTimerElapse();
private:
	static UINT getTimerElapseFromTempo(UCHAR tempo);
	BOOL compositionEnded();

	Callback* compositionEndCallback;
	Callback* changeNoteCallback;
	UCHAR trackCount;
	MidiTrack** tracks;
	BOOL* trackEnded;
	MidiDevice* midiDevice;
	UINT timerElapse;
	MidiTrack* selectedTrack;
};

