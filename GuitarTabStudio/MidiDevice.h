#pragma once
#include "Midi.h"
#include <mmsystem.h>

class MidiDevice {
public:
	MidiDevice();
	~MidiDevice();
	BOOL open();
	void close();
	void sendMessage(MidiMessage midiMessage);
private:
	BOOL closed;
	HMIDIOUT hMidi;
};

