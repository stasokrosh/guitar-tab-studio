#include "stdafx.h"
#include "MidiEvent.h"


MidiEvent::MidiEvent(UCHAR duration, UCHAR channel, Callback* changeNoteCallback) {
	this->startDuration = duration;
	this->currentDuration = duration;
	this->channel = channel;
	this->changeNoteCallback = changeNoteCallback;
}

BOOL MidiEvent::play(MidiDevice* midiDevice) {
	currentDuration--;
	return currentDuration == 0;
}

Callback* MidiEvent::getChangeNoteCallback() {
	return this->changeNoteCallback;
}
