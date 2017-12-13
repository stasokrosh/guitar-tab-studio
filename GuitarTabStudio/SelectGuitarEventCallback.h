#pragma once
#include "Callback.h"
#include "NotesEditor.h"
#include "GuitarTrackEditor.h"


class SelectGuitarEventCallback : public Callback {
public:
	SelectGuitarEventCallback(NotesEditor* notesEditor, GuitarTrackEditor* trackEditor, Event* event);
	~SelectGuitarEventCallback();
	virtual void call();
private:
	GuitarTrackEditor* trackEditor;
	NotesEditor* notesEditor;
	Event* event;
};

