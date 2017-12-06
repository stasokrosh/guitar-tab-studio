#pragma once
#include "StringInstrument.h"
class Guitar : public StringInstrument {
public:
	Guitar(UCHAR number, string name, UCHAR capo);
	~Guitar();
	virtual void initializeStrings();
	UCHAR capo;
};

