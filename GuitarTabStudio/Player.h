#pragma once
#include "MidiPlayer.h"
#include "Timer.h"

class Player {
public:
	Player(NotesEditor* notesEditor, Timer* timer);
	~Player();
	void play();
	void pause();
	void resume();
	void stop();
	BOOL getPlaying();
private:
	BOOL playing;
	BOOL stopped;
	MidiPlayer* midiPlayer;
	NotesEditor* notesEditor;
	class PlayerEndPlayingCallback : public Callback{
	public:
		PlayerEndPlayingCallback(Player* player);
		virtual void call();
	private:
		Player* player;
	};
};

