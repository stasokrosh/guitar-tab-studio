#include "stdafx.h"
#include "Guitar.h"


Guitar::Guitar(UCHAR number, wstring name, UCHAR stringCount, Note* defaultFormation, UCHAR capo) : Instrument(number, name, GUITAR) {
	this->stringCount = stringCount;
	this->formation = new Note[stringCount];
	for (int i = 0; i < stringCount; i++) {
		this->formation[i] = defaultFormation[i];
	}
}


Guitar::~Guitar() {
}

UCHAR Guitar::getStringCount() {
	return this->stringCount;
}

UCHAR Guitar::getFrequency(CHAR note, UCHAR stringNum) {
	return GetFrequency(this->formation[stringNum].octave, this->formation[stringNum].frequency) + note;
}

Note * Guitar::getString(UCHAR stringNum) {
	return &this->formation[stringNum];
}

UCHAR Guitar::getCapo() {
	return this->capo;
}

void Guitar::setCapo(UCHAR capo) {
	this->capo = capo;
}
