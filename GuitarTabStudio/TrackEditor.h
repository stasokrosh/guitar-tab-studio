#pragma once
#include "Common.h"
#include "Track.h"
#include <vector>
#include "ViewInfo.h"
#include "TrackViewComponent.h"
#include "SelectedEvent.h"
#include "MidiTrack.h"

using namespace std;

class TrackEditor {
public:
	TrackEditor(Track* track, Callback* updateCallback);
	virtual ~TrackEditor();
	Track* getTrack();
	void setSelectedEvent(SelectedEvent* selectedEvent);
	void setTrackInfo(TrackInfo* trackInfo);
	MidiTrack* getMidiTrack(UCHAR channel, MidiDevice* midiDevice, TactInfo* tact, BOOL selected);
	virtual TactIterator* getTactByTactInfo(TactInfo* tactInfo);
	virtual TactIterator* getTactByEvent(EventIterator* eventIterator);
	virtual TrackViewComponent* getTrackViewComponent(ViewInfo* viewInfo, CompositionInfo* compositionInfo) = 0;
	virtual void Write(wofstream* stream) = 0;
	virtual BOOL Load(wifstream* stream, vector<TactInfo*>* tacts) = 0;
	virtual void preparePlaying() = 0;
	virtual void moveForward() = 0;
	virtual void moveBackwards() = 0;
protected:
	Track* track;
	SelectedEvent* selectedEvent;
	Callback* updateCallback;

	virtual MidiEvent* getMidiEvent(Event* event, UCHAR channel,Callback* selectEventCallback) = 0;
private:
	void addMidiEventsToVector(TactIterator* iterator, UCHAR channel, vector<MidiEvent*>* events, BOOL selected);
	static void MoveSelectorBack(TactIterator* current, TactIterator* begin);
	static void CreateNewReprise(TactIterator* current, TactIterator* begin, vector<pair<Tact*, UCHAR>>* repriseStack);
};

