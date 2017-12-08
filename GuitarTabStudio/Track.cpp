#include "stdafx.h"
#include "Track.h"

Track::Track(TrackInfo trackInfo, UCHAR velocity, Composition* composition) {
	this->trackInfo = trackInfo;
	this->composition = composition;
	this->setVelocity(velocity);
}

Track::~Track() {
	delete this->trackInfo.instrument;
}

TactIterator Track::addTact(TactInfo* tactInfo) {
	return Sequence<Tact>::addElement(new Tact(tactInfo, this));
}

void Track::insertTact(TactIterator iterator, TactInfo* tactInfo) {
	Sequence<Tact>::insertElement(iterator, new Tact(tactInfo, this));
}


MidiTrack * Track::getMidiTrack(UCHAR channel, MidiDevice * midiDevice, TactInfo* tactInfo) {
	TactIterator begin = this->findTactByTactInfo(tactInfo);
	TactIterator current = begin;
	TactIterator end = this->getEnd();
	vector<MidiEvent*>* events = new vector<MidiEvent*>();
	vector<pair<TactIterator, UCHAR>> repriseStack;
	while (current != end) {
		(*current)->addMidiEventsToVector(channel, &(this->effectiveVelocity), events);
		if (repriseStack.size() > 0) {
			pair<TactIterator, UCHAR> currentReprise = repriseStack.back();
			if (current == currentReprise.first) {
				currentReprise.second--;
				if (currentReprise.second == 0) {
					repriseStack.pop_back();
					current++;
				} else {
					this->moveIteratorBack(current, begin);
				}
			} else {
				this->createNewReprise(current, begin, &repriseStack);
			}
		} else {
			this->createNewReprise(current, begin, &repriseStack);
		}
	}
}

TactIterator Track::findTactByTactInfo(TactInfo * tactInfo) {
	TactIterator iterator = this->getBegin();
	TactIterator end = this->getEnd();
	while (iterator != end && (*iterator)->getTactInfo() != tactInfo) {
		iterator++;
	}
	return iterator;
}

BOOL Track::isValid() {
	TactIterator iterator = this->getBegin();
	TactIterator end = this->getEnd();
	while (iterator != end) {
		if (!(*iterator)->isValid()) {
			return FALSE;
		}
		iterator++;
	}
	return TRUE;
}

UCHAR Track::getVelocity() {
	return this->velocity;
}

void Track::setVelocity(UCHAR velocity) {
	this->velocity = velocity;
	this->effectiveVelocity = velocity * this->composition->getVelocity / 0xFF;
}

Composition * Track::getComposition() {
	return this->composition;
}

TrackInfo * Track::getTrackInfo() {
	return &(this->trackInfo);
}

TactIterator Track::moveIteratorBack(TactIterator current, TactIterator begin) {
	while (current != begin || (*current)->getTactInfo()->repriseBegin) {
		current--;
	}
	return current;
}

TactIterator Track::createNewReprise(TactIterator current, TactIterator begin, vector<pair<TactIterator, UCHAR>>* repriseStack) {
	if ((*current)->getTactInfo()->repriseEnd > 1) {
		pair<TactIterator, UCHAR> newReprise(current, (*current)->getTactInfo()->repriseEnd - 1);
		repriseStack->push_back(newReprise);
		this->moveIteratorBack(current, begin);
	} else {
		current++;
	}
	return current;
}

