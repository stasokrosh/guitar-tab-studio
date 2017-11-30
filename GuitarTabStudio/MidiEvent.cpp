#include "stdafx.h"
#include "MidiEvent.h"


MidiEvent::MidiEvent(UCHAR duration, UCHAR channel) {
	this->startDuration = duration;
	this->currentDuration = duration;
	this->channel = channel;
}

BOOL MidiEvent::play(MidiDevice* midiDevice) {
	currentDuration--;
	return currentDuration == 0;
}
