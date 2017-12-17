#include "stdafx.h"
#include "Player.h"


void Player::play() {
	this->midiPlayer->play(this->notesEditor->createMidiComposition(this->midiPlayer->getMidiDevice()));
	this->playing = TRUE;
}

void Player::pause() {
	this->midiPlayer->pause();
	this->stopped = TRUE;
}

void Player::resume() {
	this->midiPlayer->resume();
	this->stopped = FALSE;
}

void Player::stop() {
	this->midiPlayer->stop();
	this->playing = FALSE;
}

BOOL Player::getPlaying() {
	return this->playing;
}

Player::Player(Timer* timer, NotesEditor* notesEditor) {
	this->notesEditor = notesEditor;
	this->midiPlayer = new MidiPlayer(timer, new PlayerEndPlayingCallback(this));
	this->playing = false;
	this->stopped = false;
}


Player::~Player() {
	delete this->midiPlayer;
}

Player::PlayerEndPlayingCallback::PlayerEndPlayingCallback(Player * player) {
	this->player = player;
}

void Player::PlayerEndPlayingCallback::call() {
	this->player->stop();
}
