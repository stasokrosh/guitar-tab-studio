#pragma once
#include "MidiMessage.h"
#include <mmsystem.h>

using namespace std;

class MidiDevice {
public:
	MidiDevice();
	~MidiDevice();
	void sendMessage(MidiMessage* midiMessage);
private:
	HMIDIOUT hMidi;
};

