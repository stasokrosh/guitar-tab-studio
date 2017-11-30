#pragma once
#include "Core.h"
#include "MidiComposition.h"
#include "MidiDevice.h"

class Composition : public Sequence<Track>{
public:
	Composition(CompositionInfo compositionInfo);
	~Composition();
	CompositionInfo compositionInfo;
	MidiComposition* createMidiComposition(MidiDevice* pMidiDevice);
};

