#pragma once
#include "Core.h"

using namespace std;

class Track : public Sequence<Tact> {
public:
	Track(TactDuration tactDuration, Instrument* pInstrument, string name);
	~Track();
	vector<Tact*>::iterator addElement(Tact* pElement);
	virtual void insertElement(vector<Tact*>::iterator iterator, Tact* pElement);
	Instrument* instrument;
	TactDuration tactDuration;
	string name
};

