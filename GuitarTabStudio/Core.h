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

struct EventInfo {
	BeatType beatType;
	BeatTypeEx beatTypeEx;
	UCHAR dotCount;
};

struct TactDuration {
	UCHAR beatCount;
	BeatType beatType;
};

struct CompositionInfo {
	string name;
	string author;
	string jenre;
	UCHAR tempo;
	TactDuration tactDuration;
};

struct TactInfo {
	BOOL repriseBegin;
	UCHAR repriseEnd;
	TactDuration* tactDuration;
};

struct TrackInfo {
	string name;
	Instrument* instrument;
};