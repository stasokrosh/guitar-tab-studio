#pragma once
#include "Track.h"
#include "NotesEditor.h"
#include "TrackViewComponent.h"


class TrackEditor {
public:
	TrackEditor(Track* track, NotesEditor* notesEditor);
	~TrackEditor();
	Track* getTrack();
	void getIteratorByTactInfo(TactInfo* tactInfo, TactIterator** tactIterator);
	void getIteratorsByEvent(TactInfo* tactInfo, TactIterator** tactIterator, EventIterator** eventIterator);
	Event* getSelectedEvent();
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	virtual TrackViewComponent* getTrackViewComponent(ViewInfo* viewInfo) = 0;
protected:
	NotesEditor* notesEditor;
private:
	Track* track;
};

