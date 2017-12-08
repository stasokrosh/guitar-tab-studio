#pragma once
#include "Instrument.h"
#include "Midi.h"

class StringInstrument : public Instrument {
public:
	StringInstrument(UCHAR number, string name, UCHAR stringCount);
	virtual ~StringInstrument();
	UCHAR getStringCount();
	UCHAR getFrequency(CHAR note, UCHAR stringNum);
protected:
	virtual void initializeStrings() = 0;
	Note* formation;
private:
	UCHAR stringCount;
};

