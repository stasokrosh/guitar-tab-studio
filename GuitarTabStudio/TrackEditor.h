#pragma once

#include "NotesEditor.h"
#include "Event.h";

class TrackEditor {
public:
	TrackEditor(Track* track, NotesEditor* notesEditor);
	~TrackEditor();
	Event* getSelectedEvent();
	Tact* getSelectedTact();
	Track* getTrack();
	void moveIteratorForward();
	void moveIteratorBackward();
private:
	NotesEditor* notesEditor;
	Track* track;
	Event* selectedEvent;
	Tact* selectedTact;
	vector<Event*>::iterator eventIterator;
};

