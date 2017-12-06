#include "stdafx.h"
#include "MidiEvent.h"


MidiEvent::MidiEvent(UCHAR duration, UCHAR channel, Event* event) {
	this->startDuration = duration;
	this->currentDuration = duration;
	this->channel = channel;
	this->event = event;
}

Event * MidiEvent::getEvent() {
	return this->event;
}

BOOL MidiEvent::play(MidiDevice* midiDevice) {
	currentDuration--;
	return currentDuration == 0;
}
