#pragma once
#include <Windows.h>
#include <string>

#define ABSOLUTE_BEAT_COUNT_BASE 192
#define DEFAULT_TEMPO 140
#define DEFAULT_BEAT_TYPE QUATER
#define DEFAULT_BEAT_TYPE_EX NORMAL

using namespace std;

enum Instruments {
	GUITAR
};

enum BeatType {
	WHOLE = 1,
	HALF = 2,
	QUATER = 4,
	EIGHTH = 8,
	SIXTEENTH = 16,
	THIRTY_SECOND = 32,
	SIXTY_FOURTH = 64
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
		this->beatType = DEFAULT_BEAT_TYPE;
		this->beatTypeEx = DEFAULT_BEAT_TYPE_EX;
		this->dotCount = 0;
		this->pause = true;
	}
	BeatType beatType;
	BeatTypeEx beatTypeEx;
	UCHAR dotCount;
	BOOL pause;
};

struct TactDuration {
	TactDuration() {
		beatCount = (UCHAR)DEFAULT_BEAT_TYPE;
		beatType = DEFAULT_BEAT_TYPE;
	}
	UCHAR beatCount;
	BeatType beatType;
};

struct CompositionInfo {
	CompositionInfo() {
		name = L"";
		author = L"";
		tempo = DEFAULT_TEMPO;
	}
	wstring name;
	wstring author;
	UCHAR tempo;
	TactDuration tactDuration;
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
	TrackInfo() {
		name = L"";
		velocity = 0x7F;
	}
	UCHAR velocity;
	wstring name;
};

