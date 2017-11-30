#include "stdafx.h"
#include "MidiPlayer.h"



MidiPlayer::MidiPlayer(Timer * timer, Callback * changeNoteCallback) {
	this->timer = timer;
	this->changeNoteCallback = changeNoteCallback;
	this->midiComposition = NULL;
}

MidiPlayer::~MidiPlayer() {}

MidiComposition* MidiPlayer::play(Composition* composition) {
	if (this->midiComposition != NULL) {
		return NULL;
	}
	this->midiComposition = composition->createMidiComposition(&midiDevice);
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

void MidiPlayer::startComposition() {
	this->midiComposition->initialize();
	this->timer->addCallBack(this->midiComposition, this->midiComposition->getTimerElapse());
}

void MidiPlayer::stopComposition() {
	this->timer->deleteCallBack(this->midiComposition);
}
