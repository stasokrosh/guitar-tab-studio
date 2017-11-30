#include "stdafx.h"
#include "Composition.h"


Composition::Composition(CompositionInfo compositionInfo) {
	this->compositionInfo = compositionInfo;
}


Composition::~Composition() {}

MidiComposition* Composition::createMidiComposition(MidiDevice* pMidiDevice) {
	return NULL;
}
