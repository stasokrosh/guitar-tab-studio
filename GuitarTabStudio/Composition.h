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
	Composition(CompositionInfo compositionInfo,UCHAR tempo, TactDuration tactDuration);
	~Composition();
	CompositionInfo compositionInfo;
	UCHAR tempo;
	MidiComposition* createMidiComposition(MidiDevice* midiDevice, Track* selectedTrack, TactInfo* selectedTact);
	virtual vector<Track*>::iterator addElement(Track* pElement);
	virtual void insertElement(TrackIterator iterator, Track* pElement);
	BOOL isValid();

	TactDuration tactDuration;
	vector<TactInfo> tactsSchema;
private:
	set<UCHAR>* validateChannelRelation();
	static UCHAR findMinValueNotInSet(UCHAR beginValue, set<UCHAR>* set);
};

