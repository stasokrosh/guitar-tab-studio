#pragma once
#include "Core.h"
#include "Sequence.h"
#include "Event.h"
#include "MidiTrack.h"
#include "EventFactory.h";

typedef vector<Event*>::iterator EventIterator;

class Tact : public Sequence<Event> {
public:
	Tact(TactInfo* tactInfo, Track* track);
	~Tact();
	BOOL isValid();
	void addMidiEventsToVector(UCHAR channel, UCHAR* velocity, vector<MidiEvent*>* vector);
	virtual EventIterator addEvent(EventInfo eventInfo, EventFactory* eventFactory);
	virtual void insertEvent(EventIterator iterator, EventInfo eventInfo, EventFactory * eventFactory);
	Track* getTrack();
	TactInfo* getTactInfo();
private: 
	Track* track;
	TactInfo* tactInfo;
};

