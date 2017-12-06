#include "stdafx.h"
#include "Instrument.h"


Instrument::Instrument(UCHAR number, string name) {
	this->number = number;
	this->name = name;
}


Instrument::~Instrument() {}

UCHAR Instrument::getNumber() {
	return this->number;
}

string Instrument::getName() {
	return this->name;
}

UCHAR Instrument::getPreferedChannel() {
	return -1;
}
