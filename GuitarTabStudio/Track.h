#pragma once
#include "Core.h"
#include "Instrument.h"
#include "Sequence.h"
#include "Tact.h"
#include "Composition.h"

#include "MidiTrack.h"
#include "MidiDevice.h"

using namespace std;

typedef vector<Tact*>::iterator TactIterator;

class Track : public Sequence<Tact> {
public:
	Track(TrackInfo trackInfo,UCHAR velocity, Composition* composition);
	~Track();
	virtual TactIterator addTact(TactInfo* tactInfo);
	virtual void insertTact(TactIterator iterator, TactInfo* tactInfo);
	MidiTrack* getMidiTrack(UCHAR channel, MidiDevice* midiDevice, TactInfo* tactInfo);
	TactIterator findTactByTactInfo(TactInfo* tactInfo);
	BOOL isValid();
	UCHAR getVelocity();
	void setVelocity(UCHAR velocity);
	Composition* getComposition();
	TrackInfo* getTrackInfo();

private:
	Composition* composition;
	TrackInfo trackInfo;
	UCHAR velocity;
	UCHAR effectiveVelocity;
	TactIterator moveIteratorBack(TactIterator current, TactIterator begin);
	TactIterator createNewReprise(TactIterator current, TactIterator begin, vector<pair<TactIterator, UCHAR>>* repriseStack);
};

