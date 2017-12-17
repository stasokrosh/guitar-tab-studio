#include "stdafx.h"
#include "MidiTrack.h"


MidiTrack::MidiTrack(UCHAR channel, UCHAR instrumentNum, MidiDevice* midiDevice, vector<MidiEvent*>* events) {
	this->initializeMessage = MidiMessage::ChangeInstrumentMessage(channel, instrumentNum);
	this->midiDevice = midiDevice;
	this->events = events;
}

void MidiTrack::initialize() {
	this->midiDevice->sendMessage(&(this->initializeMessage));
}


MidiEvent * MidiTrack::getCurrentEvent() {
	return *this->events->begin();
}


BOOL MidiTrack::play() {
	if (this->getCurrentEvent()->play(this->midiDevice)) {
		this->events->erase(this->events->begin(), this->events->begin());
		if (this->events->size() != 0) {
			this->getCurrentEvent()->getChangeNoteCallback()->call();
		}
	}
	return this->events->size() == 0;
}

MidiTrack::~MidiTrack() {
	delete this->events;
}
