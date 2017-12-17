#include "stdafx.h"
#include "SixStringGuitarFactory.h"


SixStringGuitarFactory::SixStringGuitarFactory() {
	this->defaultNoteFormation = new Note[6];
	this->defaultNoteFormation[0].frequency = E;
	this->defaultNoteFormation[0].octave = 4;
	this->defaultNoteFormation[1].frequency = H;
	this->defaultNoteFormation[1].octave = 3;
	this->defaultNoteFormation[2].frequency = G;
	this->defaultNoteFormation[2].octave = 3;
	this->defaultNoteFormation[3].frequency = D;
	this->defaultNoteFormation[3].octave = 3;
	this->defaultNoteFormation[4].frequency = A;
	this->defaultNoteFormation[4].octave = 2;
	this->defaultNoteFormation[5].frequency = E;
	this->defaultNoteFormation[5].octave = 2;
}


SixStringGuitarFactory::~SixStringGuitarFactory() {
	delete [] this->defaultNoteFormation;
}

Guitar * SixStringGuitarFactory::createGuitar(UCHAR instrumentNum, wstring name) {
	return new Guitar(instrumentNum, name, 6, this->defaultNoteFormation, 0);
}

wstring SixStringGuitarFactory::getGuitarTypeName() {
	return SIX_STRING_GUITAR_TYPE_NAME;
}
