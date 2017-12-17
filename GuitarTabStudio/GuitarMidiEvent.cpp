#include "stdafx.h"
#include "GuitarMidiEvent.h"


GuitarMidiEvent::GuitarMidiEvent(UCHAR duration, UCHAR channel, vector<UCHAR> notes,
	ChordDirections chordDirection, UCHAR* velocity, Callback* callback) : MidiEvent(duration, channel, callback) {
	this->chordDirection = chordDirection;
	this->notes = notes;
	this->velocity = velocity;
}


GuitarMidiEvent::~GuitarMidiEvent() {}

BOOL GuitarMidiEvent::play(MidiDevice * midiDevice) {
	UCHAR delta = this->getCurrentDelta();
	switch (this->chordDirection) {
	case NONE: {
		if (!delta) {
			this->playAll(midiDevice);
		}
	} break;
	case UP: {
		if (delta < this->notes.size()) {
			this->play(this->notes.size() - 1 - this->notes.at(delta), midiDevice);
		}
	} break;
	case DOWN: {
		if (delta < this->notes.size()) {
			this->play(this->notes.at(delta), midiDevice);
		}
	}
	}
	BOOL result = MidiEvent::play(midiDevice);
	if (!result) {
		this->stopAll(midiDevice);
	}
	return result;
}

UCHAR GuitarMidiEvent::getCurrentDelta() {
	return this->startDuration - this->currentDuration;
}

void GuitarMidiEvent::play(UCHAR noteNum, MidiDevice* midiDevice) {
	MidiMessage message = MidiMessage::StartNoteMessage(this->channel, this->notes[noteNum], *(this->velocity));
	midiDevice->sendMessage(&message);
}

void GuitarMidiEvent::stop(UCHAR noteNum, MidiDevice * midiDevice) {
	MidiMessage message = MidiMessage::StopNoteMessage(this->channel, this->notes[noteNum]);
	midiDevice->sendMessage(&message);
}

void GuitarMidiEvent::playAll(MidiDevice * midiDevice) {
	for (int i = 0; i < this->notes.size(); i++) {
		this->play(i, midiDevice);
	}
}

void GuitarMidiEvent::stopAll(MidiDevice * midiDevice) {
	for (int i = 0; i < this->notes.size(); i++) {
		this->stop(i, midiDevice);
	}
}
