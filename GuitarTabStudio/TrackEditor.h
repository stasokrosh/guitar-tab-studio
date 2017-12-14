#pragma once
#include "Track.h"
#include "NotesEditor.h"
#include "TrackViewComponent.h"
#include <fstream>

using namespace std;

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
	virtual void Write(wofstream* stream) = 0;
	virtual BOOL Load(wifstream* stream, vector<TactInfo*>* tacts, TactIterator** selectedTact, 
		EventIterator** selectedEvent) = 0;
protected:
	NotesEditor* notesEditor;
private:
	Track* track;
};

