#include "stdafx.h"
#include "MidiPlayer.h"



MidiPlayer::MidiPlayer(Timer * timer, Callback* stopCompositionCallback) {
	this->timer = timer;
	this->midiComposition = NULL;
	this->stopCompositionCallback = stopCompositionCallback;
}

MidiPlayer::~MidiPlayer() {
	if (this->midiComposition != NULL) {
		delete this->midiComposition;
	}
	if (this->stopCompositionCallback != NULL) {
		delete this->stopCompositionCallback;
	}
}

MidiComposition* MidiPlayer::play(MidiComposition* composition) {
	if (this->midiComposition != NULL) {
		return NULL;
	}
	this->midiComposition = composition;
	this->midiComposition->setCompositionEndCallback(this->stopCompositionCallback);
	this->startComposition();
	return this->midiComposition;
}

BOOL MidiPlayer::pause() {
	if (this->midiComposition == NULL) {
		return FALSE;
	}
	this->stopComposition();
	return TRUE;
}

BOOL MidiPlayer::stop() {
	if (this->midiComposition == NULL) {
		return FALSE;
	}
	this->stopComposition();
	delete this->midiComposition;
	this->midiComposition = NULL;
	return TRUE;
}

BOOL MidiPlayer::resume() {
	if (this->midiComposition == NULL) {
		return FALSE;
	}
	this->startComposition();
	return TRUE;
}

MidiDevice * MidiPlayer::getMidiDevice() {
	return &(this->midiDevice);
}

void MidiPlayer::startComposition() {
	this->midiComposition->initialize();
	this->timer->addCallBack(this->midiComposition, this->midiComposition->getTimerElapse());
}

void MidiPlayer::stopComposition() {
	this->timer->deleteCallBack();
}

