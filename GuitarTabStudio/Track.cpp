#include "stdafx.h"
#include "Track.h"

Track::Track(TactDuration tactDuration, Instrument* pInstrument, string name) {
	this->tactDuration = tactDuration;
	this->instrument = pInstrument;
	this->name = name;
}

Track::~Track() {}

vector<Tact*>::iterator Track::addElement(Tact* pElement) {
	pElement->pTactDuration = &(this->tactDuration);
	return Sequence<Tact>::addElement(pElement);
}

void Track::insertElement(vector<Tact*>::iterator iterator, Tact* pElement) {
	pElement->pTactDuration = &(this->tactDuration);
	Sequence<Tact>::insertElement(iterator, pElement);
}

