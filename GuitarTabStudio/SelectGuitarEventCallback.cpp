#include "stdafx.h"
#include "SelectGuitarEventCallback.h"


SelectGuitarEventCallback::SelectGuitarEventCallback(NotesEditor* notesEditor,GuitarTrackEditor* trackEditor, Event* event) {
	this->notesEditor = notesEditor;
	this->event = event;
	this->trackEditor = trackEditor;
}


SelectGuitarEventCallback::~SelectGuitarEventCallback() {}

void SelectGuitarEventCallback::call() {
	notesEditor->selectEvent(this->event);
	trackEditor->deselectString();
}
