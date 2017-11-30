#pragma once
#include "Midi.h"
#include <mmsystem.h>
#include <exception>

using namespace std;

class MidiDevice {
public:
	MidiDevice();
	~MidiDevice();
	void sendMessage(MidiMessage midiMessage);
private:
	HMIDIOUT hMidi;
};

