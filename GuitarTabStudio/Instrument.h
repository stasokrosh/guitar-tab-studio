#pragma once
#include "Core.h"
#include <string>

using namespace std;

class Instrument {
public:
	Instrument(UCHAR number, string name);
	~Instrument();
	UCHAR getNumber();
	string getName();
	virtual UCHAR getPreferedChannel();
private:
	UCHAR number;
	string name;
};

