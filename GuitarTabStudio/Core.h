#pragma once
#include <Windows.h>
#include <string>

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

struct TactInfo {
	BOOL repriseBegin;
	UCHAR repriseEnd;
};