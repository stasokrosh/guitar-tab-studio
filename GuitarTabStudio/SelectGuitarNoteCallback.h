#pragma once
#include "Callback.h"
#include "NotesEditor.h"
#include "GuitarTrackEditor.h"

class SelectGuitarNoteCallback :
	public Callback {
public:
	SelectGuitarNoteCallback(NotesEditor* notesEditor, GuitarTrackEditor* trackEditor, Event* event, UCHAR stringNum);
	~SelectGuitarNoteCallback();
	virtual void call();
private:
	NotesEditor* notesEditor;
	GuitarTrackEditor* guitarTrackEditor;
	Event* event;
	UCHAR stringNum;
};

