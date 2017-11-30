#pragma once
#include "Callback.h"
#include "MidiDevice.h"

class MidiComposition : public Callback {
public:
	MidiComposition(MidiDevice* midiDevice,UCHAR tempo);
	~MidiComposition();
	void initialize();
	void setChangeNoteCallBack(Callback* changeNoteCallBack);
	void call();
	UINT getTimerElapse();
private:
	Callback* changeNoteCallback;
	MidiDevice* midiDevice;
	UINT timerElapse;
};

