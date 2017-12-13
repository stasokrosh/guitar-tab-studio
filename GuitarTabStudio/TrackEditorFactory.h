#pragma once
#include "TrackEditor.h"

class TrackEditorFactory {
public:
	virtual TrackEditor* createTrackEditor(wstring instrumentName, TrackInfo trackInfo, NotesEditor* notesEditor) = 0;
	virtual Instruments getInstrumentType() = 0;
};