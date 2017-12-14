#pragma once
#include "Composition.h"
#include "FactoryOfTrackEditorFactory.h"
#include "Serialization.h"

#include <set>
#include <fstream>

class NotesEditor {
public:
	NotesEditor(FactoryOfTrackEditorFactory* factoryOfTEFactory);
	~NotesEditor();
	void createComposition(CompositionInfo compositionInfo);
	BOOL loadComposition(wstring name);
	void saveComposition(wstring name);
	void saveComposition();
	wstring getFileName();
	BOOL addTrack(TrackInfo trackInfo, Instruments instrumentType, wstring instrumentName);
	Composition* getComposition();
	MidiComposition* createMidiComposition(MidiDevice* midiDevice);
	vector<Track*> getTracks();
	EventInfo getEventInfo();
	void deleteTrack(Track* track);
	void selectTrack(Track* track);
	void selectTact(Tact* tactInfo);
	void selectEvent(Event* event);
	Track* getSelectedTrack();
	void setEventPause();
	void moveForward();
	void moveBackward();
	Tact* getSelectedTact();
	Event* getSelectedEvent();
private:
	Composition* composition;
	FactoryOfTrackEditorFactory* factoryOfTEFactory;
	vector<TrackEditor*> trackEditors;
	TrackEditor* selectedTrackEditor;
	TactIterator* selectedTact;
	EventIterator* selectedEvent;
	BOOL tactSelected;
	EventInfo eventInfo;
	wstring fileName;

	void addEmptyTact(Track* track, vector<EventInfo> events, TactInfo* tactInfo);
	void moveNextTact();
	void movePrevTact();
	void setTactSelected(BOOL tactSelected);
	set<UCHAR>* validateChannelRelation();
	void selectTrackEditor(TrackEditor* trackEditor);
	BOOL emptyEnding();
	void deleteEnding();
	TrackEditor* findTrackEditorByTrack(Track* track);
	vector<TrackEditor*>::iterator findTrackEditorIteratorByTrack(Track* track);
	void clearComposition();
	static UCHAR FindMinValueNotInSet(UCHAR beginValue, set<UCHAR>* set);
	static vector<EventInfo> GetEventsForTactDuration(TactDuration* tactDuration);
};

