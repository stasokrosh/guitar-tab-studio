#pragma once
#include "Common.h"
#include "Event.h"
#include "EventFactory.h"
#include "MidiEvent.h"
#include "EventIterator.h"
#include <vector>

using namespace std;

class Tact {
public:
	Tact(TactInfo* tactInfo, EventFactory* eventFactory);
	~Tact();
	TactValidity isValid();
	void addMidiEventsToVector(UCHAR channel, UCHAR* velocity, vector<MidiEvent*>* vector);
	TactInfo* getTactInfo();
	BOOL isEmpty();
	static USHORT getTactAbsoluteBeatCount(TactDuration* tactDuration);
	virtual EventIterator* pushEvent(EventInfo eventInfo) = 0;
	virtual void popEvent() = 0;
	virtual Event* getFront() = 0;
	virtual Event* getBack() = 0;
	virtual UCHAR getSize() = 0;
	virtual EventIterator* getBegin() = 0;
	virtual EventIterator* getEnd() = 0;
protected: 
	TactInfo* tactInfo;
	EventFactory* eventFactory;
};

