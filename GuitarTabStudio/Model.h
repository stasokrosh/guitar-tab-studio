#pragma once
#include "NotesEditor.h"
#include "TrackViewComponent.h"

class Model {
public:
	virtual BOOL initialize() = 0;
	virtual NotesEditor* getNotesEditor() = 0;
	virtual TrackViewComponent* getTrackViewComponent() = 0;
};

