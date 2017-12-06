#include "stdafx.h"
#include "StringInstrumentChordMidiEvent.h"


StringInstrumentChordMidiEvent::StringInstrumentChordMidiEvent(UCHAR duration, UCHAR channel, StringInstrumentChordEvent* event,
	vector<UCHAR> notes, ChordDirections chordDirection, UCHAR* velocity) : MidiEvent(duration, channel, event) {
	this->chordDirection = chordDirection;
	this->notes = notes;
	this->velocity = velocity;

}


StringInstrumentChordMidiEvent::~StringInstrumentChordMidiEvent() {}

BOOL StringInstrumentChordMidiEvent::play(MidiDevice * midiDevice) {
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

UCHAR StringInstrumentChordMidiEvent::getCurrentDelta() {
	return this->startDuration - this->currentDuration;
}

void StringInstrumentChordMidiEvent::play(UCHAR noteNum, MidiDevice* midiDevice) {
	MidiMessage message = MidiMessage::StartNoteMessage(this->channel, this->notes[noteNum], *(this->velocity));
	midiDevice->sendMessage(&message);
}

void StringInstrumentChordMidiEvent::stop(UCHAR noteNum, MidiDevice * midiDevice) {
	MidiMessage message = MidiMessage::StopNoteMessage(this->channel, this->notes[noteNum]);
	midiDevice->sendMessage(&message);
}

void StringInstrumentChordMidiEvent::playAll(MidiDevice * midiDevice) {
	for (int i = 0; i < this->notes.size(); i++) {
		this->play(i, midiDevice);
	}
}

void StringInstrumentChordMidiEvent::stopAll(MidiDevice * midiDevice) {
	for (int i = 0; i < this->notes.size(); i++) {
		this->stop(i, midiDevice);
	}
}
