#include "stdafx.h"
#include "Composition.h"

Composition::Composition(CompositionInfo compositionInfo) {
	this->compositionInfo = compositionInfo;
}


Composition::~Composition() {
	for (Track* track : this->tracks) {
		delete track;
	}
}


BOOL Composition::isValid() {
	for (Track* track : this->tracks) {
		if (!track->isValid()) {
			return FALSE;
		}
	}
	return TRUE;
}

void Composition::setTempo(UCHAR tempo) {
	this->compositionInfo.tempo = tempo;
}

void Composition::setTactDuration(TactDuration tactDuration) {
	this->compositionInfo.tactDuration = tactDuration;
}

void Composition::pushTactInfo(TactInfo* tactInfo) {
	this->tactsSchema.push_back(tactInfo);
}

void Composition::deleteTactInfo(TactInfo* tactInfo) {
	vector<TactInfo*>::iterator current = this->tactsSchema.begin();
	vector<TactInfo*>::iterator end = this->tactsSchema.end();
	while (current != end) {
		if (*current = tactInfo) {
			this->tactsSchema.erase(current, current);
			return;
		}
		current++;
	}
}

void Composition::popTactInfo() {
	this->tactsSchema.pop_back();
}


UCHAR Composition::getSize() {
	return this->tracks.size();
}

wstring Composition::getName() {
	return this->compositionInfo.name;
}

wstring Composition::getAuthor() {
	return this->compositionInfo.author;
}

UCHAR Composition::getTempo() {
	return this->compositionInfo.tempo;
}

TactDuration* Composition::getTactDuration() {
	return &(this->compositionInfo.tactDuration);
}

SHORT Composition::getTactInfoCount() {
	return this->tactsSchema.size();
}

TactInfo* Composition::getTactInfo(UCHAR number) {
	return this->tactsSchema.at(number);
}

CompositionInfo * Composition::getCompositionInfo() {
	return &(this->compositionInfo);
}

void Composition::setName(wstring name) {
	this->compositionInfo.name = name;
}

void Composition::setAuthor(wstring author) {
	this->compositionInfo.author = author;
}

Track * Composition::getTrack(UCHAR number) {
	return this->tracks.at(number);
}

Track * Composition::addTrack(Track* track) {
	this->tracks.push_back(track);
	return this->tracks.back();
}

void Composition::deleteTrack(UCHAR number) {
	UCHAR i = 0;
	vector<TactInfo*>::iterator current = this->tactsSchema.begin();
	vector<TactInfo*>::iterator end = this->tactsSchema.end();
	while (i < number && current != end) {
		current++;
	}
	if (current != end) {
		this->tactsSchema.erase(current, current);
	}
}




