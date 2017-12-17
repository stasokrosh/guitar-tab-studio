#include "stdafx.h"
#include "Event.h"

Event::Event(EventInfo eventInfo) {
	this->eventInfo = eventInfo;
}

Event::~Event() {
}

UCHAR Event::getAbsoluteBeatCount() {
	return Event::getAbsoluteBeatCount(&this->eventInfo);
}


BOOL Event::isPause() {
	return this->eventInfo.pause;
}

void Event::setBeatType(BeatType beatType) {
	this->eventInfo.beatType = beatType;
}

void Event::setBeatTypeEx(BeatTypeEx beatTypeEx) {
	this->eventInfo.beatTypeEx = beatTypeEx;
}

void Event::setDotCount(UCHAR dotCount) {
	this->eventInfo.dotCount = dotCount;
}

void Event::setPause(BOOL pause) {
	this->eventInfo.pause = pause;
}


UCHAR Event::getAbsoluteBeatCount(EventInfo * eventInfo) {
	UCHAR absoluteBeatCount = ABSOLUTE_BEAT_COUNT_BASE / (1 << eventInfo->beatType) * NORMAL / eventInfo->beatTypeEx;
	absoluteBeatCount = absoluteBeatCount * 2 - absoluteBeatCount / (1 << eventInfo->dotCount);
	return absoluteBeatCount;
}

EventInfo * Event::getEventInfo() {
	return &this->eventInfo;
}

BeatType Event::getBeatType() {
	return this->eventInfo.beatType;
}

BeatTypeEx Event::getBeatTypeEx() {
	return this->eventInfo.beatTypeEx;
}

UCHAR Event::getDotCount() {
	return this->eventInfo.dotCount;
}