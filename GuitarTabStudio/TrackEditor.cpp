#include "stdafx.h"
#include "TrackEditor.h"


TrackEditor::TrackEditor(Track* track, NotesEditor* notesEditor) {
	this->track = track;
	this->notesEditor = notesEditor;
}


TrackEditor::~TrackEditor() {
	delete this->track;
}

Track * TrackEditor::getTrack() {
	return this->track;
}

void TrackEditor::getIteratorByTactInfo(TactInfo * tactInfo, TactIterator ** tactIterator) {
	*tactIterator = this->track->findIteratorByTactInfo(tactInfo);
}

void TrackEditor::getIteratorsByEvent(TactInfo * tactInfo, TactIterator ** tactIterator, EventIterator ** eventIterator) {}

Event * TrackEditor::getSelectedEvent() {
	return this->notesEditor->getSelectedEvent();
}

