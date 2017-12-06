#pragma once
#include "Core.h"
#include "Sequence.h"
#include "Event.h"
#include "MidiTrack.h"

typedef vector<Event*>::iterator EventIterator;

class Tact : public Sequence<Event>{
public:
	Tact(TactDuration* pTactDuration, TactInfo* pTactInfo);
	~Tact();
	TactValidity isValid();
	void addMidiEventsToVector(UCHAR channel, vector<MidiEvent*>* vector);
	virtual vector<Event*>::iterator addElement(Event* pElement);
	virtual void insertElement(EventIterator iterator, Event* pElement);
	Track* track;
	TactInfo* pTactInfo;
	TactDuration* pTactDuration;
};

