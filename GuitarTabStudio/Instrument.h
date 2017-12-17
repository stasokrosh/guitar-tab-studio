#pragma once
#include "Common.h"
#include <string>

using namespace std;

class Instrument {
public:
	Instrument(UCHAR number, wstring name, Instruments instrumentType);
	~Instrument();
	UCHAR getNumber();
	wstring getName();
	Instruments getInstrumentType();
	virtual UCHAR getPreferedChannel();
private:
	Instruments instrumentType;
	UCHAR number;
	wstring name;
};

