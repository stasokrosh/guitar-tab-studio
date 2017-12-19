#include "stdafx.h"
#include "GuitarEvent.h"


GuitarEvent::GuitarEvent(EventInfo eventInfo, Guitar* guitar, ChordDirections chordDirection) : 
	Event(eventInfo) {
	this->guitar = guitar;
	this->chordDirection = chordDirection;
	this->notes = new CHAR[guitar->getStringCount()];
	for (UCHAR i = 0; i < guitar->getStringCount(); i++) {
		this->notes[i] = -1;
	}
}


GuitarEvent::~GuitarEvent() {
	delete[] this->notes;
}

BOOL GuitarEvent::isEmpty() {
	if (this->isPause()) {
		return FALSE;
	}
	for (int i = 0; i < this->guitar->getStringCount(); i++) {
		if (this->notes[i] >= 0) {
			return FALSE;
		}
	}
	return TRUE;
}

void GuitarEvent::setEmpty() {
	for (int i = 0; i < this->guitar->getStringCount(); i++) {
		notes[i] = -1;
	}
	this->eventInfo.pause = FALSE;
}

void GuitarEvent::setPause(BOOL pause) {
	Event::setPause(pause);
	if (!pause) {
		this->setEmpty();
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



