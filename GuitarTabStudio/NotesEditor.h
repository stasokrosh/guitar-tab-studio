#pragma once
#include "Composition.h"
#include "FactoryOfTrackEditorFactory.h"
#include "Serialization.h"
#include "TrackEditor.h"
#include "TrackEditorFactory.h"
#include "MidiComposition.h"
#include "Event.h"
#include "SelectedEvent.h"

#include <set>
#include <vector>

using namespace std;

class TrackEditor;

class NotesEditor {
public:
	NotesEditor(FactoryOfTrackEditorFactory* factoryOfTEFactory, Callback* updateCallback);
	~NotesEditor();
	void createComposition(CompositionInfo compositionInfo);
	BOOL loadComposition(wstring name);
	void saveComposition(wstring name);
	void saveComposition();
	wstring getFileName();
	BOOL addTrack(TrackInfo trackInfo, Instruments instrumentType, wstring instrumentName);
	MidiComposition* createMidiComposition(MidiDevice* midiDevice);
	vector<Track*> getTracks();
	Event* getSelectedEvent();
	TactInfo* getSelectedTact();
	void deleteTrack(Track* track);
	void selectTrack(Track* track);
	Track* getSelectedTrack();
	Composition* getComposition();
	TrackEditor* getSelectedTrackEditor();
	FactoryOfTrackEditorFactory* getFactory();
	void setEventPause(BOOL pause);
	void setBeatType(BeatType beatType);
	void setBeatTypeEx(BeatTypeEx beatTypeEx);
	void setDotCount(UCHAR dotCount);
	void setRepriseBegin(BOOL begin, TactInfo* tactInfo);
	void setRepriseEnd(UCHAR repriseCount, TactInfo* tactInfo);
	void setCompositionInfo(CompositionInfo* compositionInfo);
	void moveForward();
	void moveBackward();
	TrackViewComponent* getTrackViewComponent(ViewInfo* viewInfo);
private:
	Composition* composition;
	FactoryOfTrackEditorFactory* factoryOfTEFactory;
	vector<TrackEditor*> trackEditors;
	TrackEditor* selectedTrackEditor;
	EventInfo eventInfo;
	wstring fileName;
	SelectedEvent* selectedEvent;
	Callback* updateCallback;
	UCHAR velocity;

	TactIterator* getSelectedTactIterator();
	void addEmptyTact(Track* track, vector<EventInfo> events, TactInfo* tactInfo);
	void moveNextTact(TactIterator* currentTact);
	void movePrevTact(TactIterator* currentTact);
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

