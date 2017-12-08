#include "stdafx.h"
#include "PauseEvent.h"


PauseEvent::PauseEvent(EventInfo eventInfo) : Event(eventInfo) {
}

MidiEvent * PauseEvent::getMidiEvent(UCHAR channel) {
	return new PauseMidiEvent(this->getAbsoluteBeatCount(), channel, this);
}


BOOL PauseEvent::isEmpty() {
	return FALSE;
}

PauseEvent::~PauseEvent() {}
