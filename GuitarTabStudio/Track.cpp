#include "stdafx.h"
#include "Track.h"

Track::Track(TrackInfo trackInfo, Instrument* instrument, TactFactory* tactFactory) {
	this->trackInfo = trackInfo;
	this->tactFactory = tactFactory;
	this->instrument = instrument;
}

Track::~Track() {
	delete this->instrument;
}

wstring Track::getName() {
	return this->trackInfo.name;
}

Instrument* Track::getInstrument() {
	return this->instrument;
}

TrackInfo* Track::getTrackInfo() {
	return &(this->trackInfo);
}

void Track::setName(wstring name) {
	this->trackInfo.name = name;
}


BOOL Track::isValid() {
	TactIterator* current = this->getBegin();
	TactIterator* end = this->getEnd();
	while (!current->equal(end)) {
		if (current->getTact()->isValid() != VALID) {
			return FALSE;
		}
		current->moveForward();
	};
	delete current;
	delete end;
	return TRUE;
}

UCHAR Track::getVelocity() {
	return this->trackInfo.velocity;
}

void Track::setVelocity(UCHAR velocity) {
	this->trackInfo.velocity = velocity;
}

