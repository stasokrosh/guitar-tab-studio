#pragma once
#include "Sequence.h"
#include "Tact.h"

#include "MidiComposition.h"
#include "MidiDevice.h"

#include <set>
#include <iterator>

typedef vector<Track*>::iterator TrackIterator;

class Composition : public Sequence<Track>{
public:
	Composition(CompositionInfo compositionInfo, UCHAR velocity);
	~Composition();
	MidiComposition* createMidiComposition(MidiDevice* midiDevice, Track* selectedTrack, TactInfo* selectedTact);
	virtual TrackIterator addTrack(TrackInfo trackInfo, UCHAR velocity);
	virtual void insertTrack(TrackIterator iterator, TrackInfo trackInfo, UCHAR velocity);
	

	BOOL isValid();
	void setVelocity(UCHAR velocity);
	UCHAR getVelocity();

private:
	UCHAR velocity;
	set<UCHAR>* validateChannelRelation();
	static UCHAR findMinValueNotInSet(UCHAR beginValue, set<UCHAR>* set);
	vector<TactInfo> tactsSchema;
	CompositionInfo compositionInfo;
};

