#pragma once
#include "Model.h"
#include "Event.h"
#include "EventIterator.h"
#include "Track.h"
#include "EventFactory.h"

class Tact {
public:
	Tact(TactInfo* tactInfo, Track* track, EventFactory* eventFactory);
	~Tact();
	TactValidity isValid();
	void addMidiEventsToVector(UCHAR channel, UCHAR* velocity, vector<MidiEvent*>* vector);
	Track* getTrack();
	TactInfo* getTactInfo();
	BOOL isEmpty();
	static USHORT getTactAbsoluteBeatCount(TactDuration* tactDuration);
	virtual void pushEvent(EventInfo eventInfo) = 0;
	virtual void popEvent() = 0;
	virtual Event* getFront() = 0;
	virtual Event* getBack() = 0;
	virtual UCHAR getSize() = 0;
	virtual EventIterator* getBegin() = 0;
	virtual EventIterator* getEnd() = 0;
protected: 
	Track* track;
	TactInfo* tactInfo;
	EventFactory* eventFactory;
};

