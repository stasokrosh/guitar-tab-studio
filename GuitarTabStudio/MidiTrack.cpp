#include "stdafx.h"
#include "MidiTrack.h"


MidiTrack::MidiTrack(UCHAR channel,Track* track, MidiDevice* midiDevice, vector<MidiEvent*>* events) {
	this->initializeMessage = MidiMessage::changeInstrumentMessage(channel, track->instrument->getNumber);
	this->track = track;
	this->changeNoteCallback = NULL;
	this->midiDevice = midiDevice;
	this->events = events;
}

void MidiTrack::initialize() {
	this->midiDevice->sendMessage(this->initializeMessage);
}

Track * MidiTrack::getTrack() {
	return this->track;
}

MidiEvent * MidiTrack::getCurrentEvent() {
	return *this->events->begin();
}

void MidiTrack::setChangeNoteCallback(Callback * changeNoteCallback) {
	this->changeNoteCallback = changeNoteCallback;
}

BOOL MidiTrack::play() {
	if (this->getCurrentEvent()->play(this->midiDevice)) {
		this->events->erase(this->events->begin(), this->events->begin());
		if (this->changeNoteCallback) {
			this->changeNoteCallback->call();
		}
	}
	return this->events->size() == 0;
}

MidiTrack::~MidiTrack() {
	delete this->initializeMessage;
	delete this->events;
}
