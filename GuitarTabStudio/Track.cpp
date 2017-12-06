#include "stdafx.h"
#include "Track.h"

Track::Track(Instrument* pInstrument, string name) {
	this->instrument = pInstrument;
	this->name = name;
}

Track::~Track() {
	delete this->instrument;
}

TactIterator Track::addElement(Tact * pElement) {
	pElement->track = this;
	return Sequence<Tact>::addElement(pElement);
}

void Track::insertElement(TactIterator iterator, Tact* pElement) {
	pElement->track = this;
	Sequence<Tact>::insertElement(iterator, pElement);
}

MidiTrack * Track::getMidiTrack(UCHAR channel, MidiDevice * midiDevice, TactInfo* tactInfo) {
	TactIterator begin = this->findTactByTactInfo(tactInfo);
	TactIterator current = begin;
	TactIterator end = this->getEnd();
	vector<MidiEvent*>* events = new vector<MidiEvent*>();
	vector<pair<TactIterator, UCHAR>> repriseStack;
	while (current != end) {
		(*current)->addMidiEventsToVector(channel, events);
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
	while (iterator != end && (*iterator)->pTactInfo != tactInfo) {
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

TactIterator Track::moveIteratorBack(TactIterator current, TactIterator begin) {
	while (current != begin || (*current)->pTactInfo->repriseBegin) {
		current--;
	}
	return current;
}

TactIterator Track::createNewReprise(TactIterator current, TactIterator begin, vector<pair<TactIterator, UCHAR>>* repriseStack) {
	if ((*current)->pTactInfo->repriseEnd > 1) {
		pair<TactIterator, UCHAR> newReprise(current, (*current)->pTactInfo->repriseEnd - 1);
		repriseStack->push_back(newReprise);
		this->moveIteratorBack(current, begin);
	} else {
		current++;
	}
	return current;
}

