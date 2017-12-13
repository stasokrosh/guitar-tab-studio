#pragma once
#include "GuitarFactory.h"
#define BASS_GUITAR_TYPE_NAME L"Bass"

class BassGuitarFactory : public GuitarFactory {
public:
	BassGuitarFactory();
	~BassGuitarFactory();
	virtual Guitar* createGuitar(UCHAR instrumentNum, wstring name);
	virtual wstring getGuitarTypeName();
private:
	Note* defaultNoteFormation;
};

