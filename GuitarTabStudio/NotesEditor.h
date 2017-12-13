#pragma once
#include "Composition.h"
#include <set>
#include "FactoryOfTrackEditorFactory.h"

class NotesEditor {
public:
	NotesEditor(FactoryOfTrackEditorFactory* factoryOfTEFactory);
	~NotesEditor();
	void CreateComposition(CompositionInfo compositionInfo);
	BOOL addTrack(TrackInfo trackInfo, Instruments instrumentType, wstring instrumentName);
	Composition* getComposition();
	MidiComposition* createMidiComposition(MidiDevice* midiDevice);
	vector<Track*> getTracks();
	EventInfo* getEventInfo();
	void deleteTrack(Track* track);
	void selectTrack(Track* track);
	void selectTact(Tact* tactInfo);
	void selectEvent(Event* event);
	Track* getSelectedTrack();
	void setEventPause();
	void moveForward();
	void moveBackward();
	void moveUp();
	void moveDown();
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
	static UCHAR findMinValueNotInSet(UCHAR beginValue, set<UCHAR>* set);
	static vector<EventInfo> getEventsForTactDuration(TactDuration* tactDuration);
};

