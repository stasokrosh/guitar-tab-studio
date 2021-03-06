#pragma once
#include "Instrument.h"
#include "Midi.h"

#define MAX_NUM 20

class Guitar : public Instrument {
public:
	Guitar(UCHAR number, wstring name, UCHAR stringCount, Note* defaultFormation, UCHAR capo);
	~Guitar();
	UCHAR getStringCount();
	UCHAR getFrequency(CHAR note, UCHAR stringNum);
	Note* getString(UCHAR stringNum);
	UCHAR getCapo();
	void setCapo(UCHAR capo);
private:
	UCHAR capo;
	Note* formation;
	UCHAR stringCount;
};

