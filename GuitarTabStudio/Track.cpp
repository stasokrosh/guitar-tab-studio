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

MidiTrack * Track::getMidiTrack(NotesEditor* notesEditor, UCHAR channel, MidiDevice * midiDevice, TactInfo* tact, Callback* changeNoteCallback) {
	TactIterator* current = this->findIteratorByTactInfo(tact);
	TactIterator* begin = this->getBegin();
	TactIterator* end = this->getEnd();
	vector<MidiEvent*>* events = new vector<MidiEvent*>();
	vector<pair<Tact*, UCHAR>> repriseStack;
	while (!current->equal(end)) {
		current->getTact()->addMidiEventsToVector(channel, &(this->effectiveVelocity), events);
		if (repriseStack.size() > 0) {
			pair<Tact*, UCHAR> currentReprise = repriseStack.back();
			if (current->getTact() == currentReprise.first) {
				currentReprise.second--;
				if (currentReprise.second == 0) {
					repriseStack.pop_back();
					current->moveForward();
				} else {
					this->moveSelectorBack(current);
				}
			} else {
				this->createNewReprise(current, &repriseStack);
			}
		} else {
			this->createNewReprise(current, &repriseStack);
		}
	}
	delete current;
	delete begin;
	delete end;
	return new MidiTrack(channel, this->instrument->getNumber(), notesEditor, midiDevice, events);
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

void Track::setComposition(Composition * composition) {
	this->composition = composition;
	this->updateVelocity();
}

UCHAR Track::getVelocity() {
	return this->trackInfo.velocity;
}

void Track::updateVelocity() {
	this->setVelocity(this->getVelocity);
}

void Track::setVelocity(UCHAR velocity) {
	this->trackInfo.velocity = velocity;
	this->effectiveVelocity = velocity * this->composition->getVelocity / 0xFF;
}

Composition * Track::getComposition() {
	return this->composition;
}

TactIterator * Track::findIteratorByTactInfo(TactInfo * tactInfo) {
	TactIterator* iterator = this->getBegin();
	while (iterator->getTact()->getTactInfo() != tactInfo) {
		iterator->moveForward();
	}
	delete iterator;
}


void Track::moveSelectorBack(TactIterator* current, TactIterator* begin) {
	while (!current->equal(begin) && !current->getTact()->getTactInfo()->repriseBegin) {
		current->moveBackwards();
	}
}

void Track::createNewReprise(TactIterator* current, vector<pair<Tact*, UCHAR>>* repriseStack) {
	if (current->getTact()->getTactInfo()->repriseEnd > 1) {
		pair<Tact*, UCHAR> newReprise(current->getTact(), current->getTact()->getTactInfo()->repriseEnd - 1);
		repriseStack->push_back(newReprise);
		this->moveSelectorBack(current);
	} else {
		current->moveForward();
	}
}