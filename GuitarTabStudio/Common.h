#pragma once
#include <Windows.h>
#include <string>
#include "Instrument.h"

#define ABSOLUTE_BEAT_COUNT_BASE 192

enum Instruments {
	GUITAR
};

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

enum TactValidity {
	VALID,
	MORE,
	LESS,
};

struct EventInfo {
	EventInfo() {
		this->beatType = QUATER;
		this->beatTypeEx = NORMAL;
		this->dotCount = 0;
		this->pause = true;
	}
	BeatType beatType;
	BeatTypeEx beatTypeEx;
	UCHAR dotCount;
	BOOL pause;
};

struct TactDuration {
	UCHAR beatCount;
	BeatType beatType;
};

struct CompositionInfo {
	wstring name;
	wstring author;
	UCHAR tempo;
	TactDuration tactDuration;
	UCHAR velocity;
};

struct TactInfo {
	TactInfo(TactDuration* tactDuration) {
		this->repriseBegin = false;
		this->repriseEnd = 1;
		this->tactDuration = tactDuration;
	}
	BOOL repriseBegin;
	UCHAR repriseEnd;
	TactDuration* tactDuration;
};

struct TrackInfo {
	UCHAR velocity;
	wstring name;
};

