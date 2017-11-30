#include "stdafx.h"
#include "MidiComposition.h"


MidiComposition::MidiComposition(MidiDevice* midiDevice, UCHAR tempo) {
	this->midiDevice = midiDevice;
}


MidiComposition::~MidiComposition() {}

void MidiComposition::initialize() {}

void MidiComposition::setChangeNoteCallBack(Callback * changeNoteCallBack) {
	this->changeNoteCallback = changeNoteCallBack;
}

void MidiComposition::call() {}

UINT MidiComposition::getTimerElapse() {
	return this->timerElapse;
}
