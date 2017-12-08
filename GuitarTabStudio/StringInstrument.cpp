#include "stdafx.h"
#include "StringInstrument.h"


StringInstrument::StringInstrument(UCHAR number, string name, UCHAR stringCount) : Instrument(number, name) {
	this->stringCount = stringCount;
	this->formation = new Note[stringCount];
	this->initializeStrings();
}


StringInstrument::~StringInstrument() {
	delete[] this->formation;
}

UCHAR StringInstrument::getStringCount() {
	return this->stringCount;
}

UCHAR StringInstrument::getFrequency(CHAR note, UCHAR stringNum) {
	return GetFrequency(this->formation[stringNum].octave, this->formation[stringNum].frequency) + note;
}
