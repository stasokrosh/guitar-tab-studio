#pragma once
#include "Event.h"
#include "Guitar.h"
#include "GuitarMidiEvent.h"
#include "PauseMidiEvent.h"
#include "GuitarEventViewComponent.h";
#include "SelectGuitarEventCallback.h"

enum ChordDirections {
	UP,
	NONE,
	DOWN
};

class GuitarEvent : public Event {
public:
	GuitarEvent(EventInfo eventInfo, Tact* tact, Guitar* Guitar, ChordDirections chordDirection);
	~GuitarEvent();
	virtual MidiEvent* getMidiEvent(UCHAR channel, UCHAR* velocity);
	virtual BOOL isEmpty();
	virtual void setEmpty();
	virtual void setPause(BOOL pause);
	CHAR* getNote(int stringNum);
	ChordDirections getChordDirection();
	void setChordDirection(ChordDirections chordDirection);
	UCHAR getStringCount();
	GuitarEventViewComponent* getViewComponent(ViewInfo* viewInfo, NotesEditor* notesEditor, GuitarTrackEditor* trackEditor);
private:
	ChordDirections chordDirection;
	CHAR* notes;
	Guitar* guitar;
};

