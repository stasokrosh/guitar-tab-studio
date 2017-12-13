#include "stdafx.h"
#include "MidiComposition.h"


MidiComposition::MidiComposition(MidiDevice* midiDevice, UCHAR tempo, MidiTrack** tracks, UCHAR trackCount) {
	this->midiDevice = midiDevice;
	this->timerElapse = MidiComposition::getTimerElapseFromTempo(tempo);
	this->trackCount = trackCount;
	this->tracks = tracks;
	this->trackEnded = new BOOL[trackCount] { FALSE }; 
}


MidiComposition::~MidiComposition() {
	if (this->compositionEndCallback) {
		delete this->compositionEndCallback;
	}
	for (int i = 0; i < this->trackCount; i++) {
		delete this->tracks[i];
	}
	delete[] this->tracks;
	delete[] this->trackEnded;
}

void MidiComposition::initialize() {
	for (int i = 0; i < this->trackCount; i++) {
		this->tracks[i]->initialize();
	}
}

void MidiComposition::setCompositionEndCallback(Callback* compositionEndCallback) {
	this->compositionEndCallback = compositionEndCallback;
}

void MidiComposition::call() {
	UCHAR i = 0;
	for (MidiTrack* midiTrack : (this->tracks)) {
		if (!this->trackEnded[i]) {
			trackEnded[i] = midiTrack->play();
		}
		i++;
	}
	if (this->compositionEnded) {
		this->compositionEndCallback->call();
	}
}

UINT MidiComposition::getTimerElapse() {
	return this->timerElapse;
}

UINT MidiComposition::getTimerElapseFromTempo(UCHAR tempo) {
	return 1000 * 60 / tempo;
}

BOOL MidiComposition::compositionEnded() {
	for (int i = 0; i < this->trackCount; i++) {
		if (!this->trackEnded[i]) {
			return FALSE;
		}
	}
	return TRUE;
}
