#include "stdafx.h"
#include "BassGuitarFactory.h"


BassGuitarFactory::BassGuitarFactory() {
	this->defaultNoteFormation[0].frequency = G;
	this->defaultNoteFormation[1].frequency = D;
	this->defaultNoteFormation[2].frequency = A;
	this->defaultNoteFormation[3].frequency = E;
}


BassGuitarFactory::~BassGuitarFactory() {
	delete[] this->defaultNoteFormation;
}

Guitar * BassGuitarFactory::createGuitar(UCHAR instrumentNum, wstring name) {
	return new Guitar(instrumentNum, name, 6, this->defaultNoteFormation, 0);
}

wstring BassGuitarFactory::getGuitarTypeName() {
	return BASS_GUITAR_TYPE_NAME;
}
