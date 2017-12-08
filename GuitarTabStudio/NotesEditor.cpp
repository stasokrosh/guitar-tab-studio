#include "stdafx.h"
#include "NotesEditor.h"


NotesEditor::NotesEditor() {
	this->eventInfo.beatType = DEFAULT_BEAT_TYPE;
	this->eventInfo.beatTypeEx = DEFAULT_BEAT_TYPE_EX;
	this->eventInfo.dotCount = DEFAULT_DOT_COUNT;
	this->composition = NULL;
}


NotesEditor::~NotesEditor() {}

void NotesEditor::CreateComposition(CompositionInfo compositionInfo) {}

void NotesEditor::LoadComposition(string fileName) {}

void NotesEditor::SaveCompositionAs(string fileName) {}

void NotesEditor::SaveComposition() {}

void NotesEditor::setBeatType(BeatType beatType) {
	this->eventInfo.beatType = beatType;
}

void NotesEditor::setBeatTypeEx(BeatTypeEx beatTypeEx) {
	this->eventInfo.beatTypeEx = beatTypeEx;
}

void NotesEditor::setDotCount(UCHAR dotCount) {
	this->eventInfo.dotCount = dotCount;
}

void NotesEditor::setCompositionInfo(CompositionInfo compositionInfo) {
	this->composition->compositionInfo = compositionInfo;
}

void NotesEditor::setTrackName(string trackName) {
	Track* selectedTrack = this->getSelectedTrack();
	selectedTrack->name = trackName;
}

BeatType NotesEditor::getBeatType() {
	return this->eventInfo.beatType;
}

BeatTypeEx NotesEditor::getBeatTypeEx() {
	return this->eventInfo.beatTypeEx;
}

UCHAR NotesEditor::getDotCount() {
	return this->eventInfo.dotCount;
}

string NotesEditor::getFileName() {
	return this->fileName;
}

CompositionInfo NotesEditor::getCompositionInfo() {
	return this->composition->compositionInfo;
}

Instrument * NotesEditor::getInstrument() {
	Track* selectedTrack = this->getSelectedTrack();
	return selectedTrack->instrument;
}

string NotesEditor::getTrackName() {
	Track* selectedTrack = this->getSelectedTrack();
	return selectedTrack->name;
}

void NotesEditor::initializeTrackEditors() {
	this->clearTrackEditorsVector();
	TrackIterator begin = this->composition->getBegin();
	TrackIterator end = this->composition->getEnd();
	while (begin != end) {
		this->trackEditors.push_back(new TrackEditor(*begin, this));
		begin++;
	}
	this->selectTrackEditor(this->trackEditors.front());
}

void NotesEditor::clearTrackEditorsVector() {
	for (TrackEditor* trackEditor : this->trackEditors) {
		delete trackEditor;
	}
	this->trackEditors.clear;
}

void NotesEditor::selectTrackEditor(TrackEditor * trackEditor) {
	this->selectedTrackEditor = trackEditor;
}

Track * NotesEditor::getSelectedTrack() {
	return this->selectedTrackEditor->getTrack();
}



