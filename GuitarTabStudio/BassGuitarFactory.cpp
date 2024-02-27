#include "stdafx.h"
#include "BassGuitarFactory.h"


BassGuitarFactory::BassGuitarFactory() {
	this->defaultNoteFormation = new Note[4];
	this->defaultNoteFormation[0].frequency = G;
	this->defaultNoteFormation[0].octave = 3;
	this->defaultNoteFormation[1].frequency = D;
	this->defaultNoteFormation[1].octave = 3;
	this->defaultNoteFormation[2].frequency = A;
	this->defaultNoteFormation[2].octave = 2;
	this->defaultNoteFormation[3].frequency = E;
	this->defaultNoteFormation[3].octave = 2;
}


BassGuitarFactory::~BassGuitarFactory() {
	delete[] this->defaultNoteFormation;
}

Guitar * BassGuitarFactory::createGuitar(UCHAR instrumentNum, wstring name) {
	return new Guitar(instrumentNum, name, 4, this->defaultNoteFormation, 0);
}

wstring BassGuitarFactory::getGuitarTypeName() {
	return BASS_GUITAR_TYPE_NAME;
}
