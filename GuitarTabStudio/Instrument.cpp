#include "stdafx.h"
#include "Instrument.h"


Instrument::Instrument(UCHAR number, wstring name, Instruments instrumentType) {
	this->number = number;
	this->name = name;
	this->instrumentType = instrumentType;
}


Instrument::~Instrument() {}

UCHAR Instrument::getNumber() {
	return this->number;
}

wstring Instrument::getName() {
	return this->name;
}

Instruments Instrument::getInstrumentType() {
	return this->instrumentType;
}

UCHAR Instrument::getPreferedChannel() {
	return -1;
}
