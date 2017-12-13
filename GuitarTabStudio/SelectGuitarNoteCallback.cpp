#include "stdafx.h"
#include "SelectGuitarNoteCallback.h"


SelectGuitarNoteCallback::SelectGuitarNoteCallback(NotesEditor* notesEditor, GuitarTrackEditor* trackEditor, Event* event, UCHAR stringNum) {
	this->notesEditor = notesEditor;
	this->guitarTrackEditor = guitarTrackEditor;
	this->event = event;
	this->stringNum = stringNum;
}


SelectGuitarNoteCallback::~SelectGuitarNoteCallback() {
}

void SelectGuitarNoteCallback::call() {
	this->notesEditor->selectEvent(this->event);
	this->guitarTrackEditor->selectString(this->stringNum);
}
