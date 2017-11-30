#pragma once
#include <Windows.h>
#include "Event.h"
#include "Tact.h"
#include "Track.h"
#include "Sequence.h"
#include "Instrument.h"
#include "Midi.h"

#include <string>
#include <vector>

#define ABSOLUTE_BEAT_COUNT_BASE 192

enum BeatType {
	WHOLE,
	HALF,
	QUATER,
	EIGHTH,
	SIXTEENTH,
	THIRTY_SECOND,
	SIXTY_FOURTH
};

enum BeatTypeEx {
	NORMAL = 2,
	TRIPLE = 3
};

struct TactDuration {
	UCHAR beatCount;
	BeatType beatType;
};

enum TactValidity {
	LESS,
	VALID,
	MORE,
};

struct CompositionInfo {
	string name;
	string author;
	string jenre;
};