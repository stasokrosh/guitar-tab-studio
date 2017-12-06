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
	Track(Instrument* pInstrument, string name);
	~Track();
	virtual vector<Tact*>::iterator addElement(Tact* pElement);
	virtual void insertElement(TactIterator iterator, Tact* pElement);
	MidiTrack* getMidiTrack(UCHAR channel, MidiDevice* midiDevice, TactInfo* tactInfo);
	TactIterator findTactByTactInfo(TactInfo* tactInfo);
	BOOL isValid();

	Composition* composition;
	Instrument* instrument;
	string name;
private:
	TactIterator moveIteratorBack(TactIterator current, TactIterator begin);
	TactIterator createNewReprise(TactIterator current, TactIterator begin, vector<pair<TactIterator, UCHAR>>* repriseStack);
};

