#pragma once
#include <Windows.h>
#include "MidiDevice.h"
#include "MidiEvent.h"
#include "MidiMessage.h"

#define OCTAVE_SIZE 12

union Message {
	ULONG fullMessage;
	UCHAR params[4];
};

enum Notes {
	C,
	Db,
	D,
	Eb,
	E,
	F,
	Gb,
	G,
	Ab,
	A,
	Hb,
	H
};

UCHAR GetFrequency(UCHAR octave, Notes note);
