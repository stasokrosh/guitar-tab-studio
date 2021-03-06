#pragma once
#include "MidiPlayer.h"
#include "Timer.h"
#include "NotesEditor.h"
#include "Callback.h"

class Player {
public:
	Player(Timer* timer, NotesEditor* notesEditor, Callback* updateCallback);
	~Player();
	void play();
	void pause();
	void resume();
	void stop();
	BOOL getPlaying();
	BOOL getStopped();
private:
	BOOL playing;
	BOOL stopped;
	MidiPlayer* midiPlayer;
	NotesEditor* notesEditor;
	Callback* updateCallback;

	class PlayerEndPlayingCallback : public Callback{
	public:
		PlayerEndPlayingCallback(Player* player);
		virtual void call();
	private:
		Player* player;
	};
};

