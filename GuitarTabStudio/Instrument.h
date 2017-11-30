#pragma once
#include "Core.h"

class Instrument {
public:
	Instrument(UCHAR number, string name);
	~Instrument();
	UCHAR getNumber();
	string getName();
private:
	UCHAR number;
	string name;
};

