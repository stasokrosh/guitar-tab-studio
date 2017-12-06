#include "stdafx.h"
#include "Guitar.h"


Guitar::Guitar(UCHAR number, string guitarName, UCHAR capo) : StringInstrument(number,guitarName + " guitar") {
	this->capo = capo;
}


Guitar::~Guitar() {}

void Guitar::initializeStrings() {
	this->formation[0].frequency = E;
	this->formation[0].octave = 1;

	this->formation[1].frequency = H;
	this->formation[1].octave = 1;

	this->formation[2].frequency = G;
	this->formation[2].octave = 1;
	
	this->formation[3].frequency = D;
	this->formation[3].octave = 1;

	this->formation[4].frequency = A;
	this->formation[4].octave = 1;

	this->formation[5].frequency = E;
	this->formation[5].octave = 1;
}
