#include "stdafx.h"
#include "PauseMidiEvent.h"


PauseMidiEvent::PauseMidiEvent(UCHAR duration, UCHAR channel, Event* event) : MidiEvent(duration, channel, event) {}


PauseMidiEvent::~PauseMidiEvent() {}
