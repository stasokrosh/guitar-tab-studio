#include "stdafx.h"
#include "GuitarEvent.h"


GuitarEvent::GuitarEvent(EventInfo eventInfo, Tact* tact, Guitar* Guitar, ChordDirections chordDirection) : 
	Event(eventInfo, tact) {
	this->guitar = Guitar;
	this->chordDirection = chordDirection;
	this->notes = new CHAR[Guitar->getStringCount] { -1 };
}


GuitarEvent::~GuitarEvent() {
	delete[] this->notes;
}

MidiEvent * GuitarEvent::getMidiEvent(UCHAR channel, UCHAR* velocity) {
	if (this->isPause()) {
		return new PauseMidiEvent(this->getAbsoluteBeatCount, channel, this);
	} else {
		vector<UCHAR> notes;
		for (int i = 0; i < this->guitar->getStringCount; i++) {
			if (this->notes[i] >= 0) {
				notes.push_back(this->guitar->getFrequency(this->notes[i], i));
			}
		}
		return new GuitarMidiEvent(this->getAbsoluteBeatCount(), channel, this, notes, this->chordDirection, velocity);
	}
}

BOOL GuitarEvent::isEmpty() {
	for (int i = 0; i < this->guitar->getStringCount; i++) {
		if (this->notes[i] >= 0) {
			return FALSE;
		}
	}
	return TRUE;
}

void GuitarEvent::setEmpty() {
	for (int i = 0; i < this->guitar->getStringCount; i++) {
		notes[i] = -1;
	}
}

void GuitarEvent::setPause(BOOL pause) {
	Event::setPause(pause);
		if (!pause) {
			this->setEmpty();
		}
	}
}

CHAR * GuitarEvent::getNote(int stringNum) {
	return &(notes[stringNum]);
}

ChordDirections GuitarEvent::getChordDirection() {
	return this->chordDirection;
}

void GuitarEvent::setChordDirection(ChordDirections chordDirection) {
	this->chordDirection = chordDirection;
}

UCHAR GuitarEvent::getStringCount() {
	return this->guitar->getStringCount();
}

GuitarEventViewComponent * GuitarEvent::getViewComponent(ViewInfo * viewInfo, NotesEditor * notesEditor, GuitarTrackEditor * trackEditor) {
	Callback* callback = new SelectGuitarEventCallback(notesEditor, trackEditor, this);
	return new GuitarEventViewComponent(viewInfo, callback, this, notesEditor, trackEditor);
}



