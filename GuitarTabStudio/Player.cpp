#include "stdafx.h"
#include "Player.h"


void Player::play() {
	this->midiPlayer->play(this->notesEditor->createMidiComposition(this->midiPlayer->getMidiDevice()));
	this->playing = TRUE;
	this->updateCallback->call();
}

void Player::pause() {
	this->midiPlayer->pause();
	this->stopped = TRUE;
	this->updateCallback->call();
}

void Player::resume() {
	this->midiPlayer->resume();
	this->stopped = FALSE;
	this->updateCallback->call();
}

void Player::stop() {
	this->midiPlayer->stop();
	this->playing = FALSE;
	this->updateCallback->call();
}

BOOL Player::getPlaying() {
	return this->playing;
}

BOOL Player::getStopped() {
	return this->stopped;
}

Player::Player(Timer* timer, NotesEditor* notesEditor, Callback* updateCallback) {
	this->notesEditor = notesEditor;
	this->midiPlayer = new MidiPlayer(timer, new PlayerEndPlayingCallback(this));
	this->updateCallback = updateCallback;
	this->playing = FALSE;
	this->stopped = FALSE;
}


Player::~Player() {
	delete this->midiPlayer;
	delete this->updateCallback;
}

Player::PlayerEndPlayingCallback::PlayerEndPlayingCallback(Player * player) {
	this->player = player;
}

void Player::PlayerEndPlayingCallback::call() {
	this->player->stop();
}
