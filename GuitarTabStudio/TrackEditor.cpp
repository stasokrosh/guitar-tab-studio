#include "stdafx.h"
#include "TrackEditor.h"


TrackEditor::TrackEditor(Track* track, NotesEditor* notesEditor) {
	this->track = track;
	this->eventIterator = (*(track->getBegin()))->getBegin();
	this->selectedEvent = *(this->eventIterator);
	this->selectedTact = NULL;
	this->notesEditor = notesEditor;
}


TrackEditor::~TrackEditor() { }

Event * TrackEditor::getSelectedEvent() {
	return this->selectedEvent;
}

Tact * TrackEditor::getSelectedTact() {
	return this->selectedTact;
}

Track * TrackEditor::getTrack() {
	return this->track;
}

void TrackEditor::moveIteratorForward() {}

void TrackEditor::moveIteratorBackward() {}
