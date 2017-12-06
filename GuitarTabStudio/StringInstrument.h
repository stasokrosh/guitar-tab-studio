#pragma once
#include "Instrument.h"
#include "Midi.h"

class StringInstrument : public Instrument {
public:
	StringInstrument(UCHAR number, string name, UCHAR stringCount);
	virtual ~StringInstrument();
	UCHAR getStringCount();
	Note operator[](UCHAR stringNum) {
		return formation[stringNum];
	}
protected:
	virtual void initializeStrings() = 0;
	Note* formation;
private:
	UCHAR stringCount;
};

