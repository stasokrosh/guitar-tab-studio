#include "stdafx.h"
#include "PauseEvent.h"


PauseEvent::PauseEvent(BeatType beatType, BeatTypeEx beatTypeEx, UCHAR dotCount) : Event(beatType, beatTypeEx, dotCount) {
}

MidiEvent * PauseEvent::getMidiEvent(UCHAR channel) {
	return new PauseMidiEvent(this->getAbsoluteBeatCount(), channel, this);
}


PauseEvent::~PauseEvent() {}
