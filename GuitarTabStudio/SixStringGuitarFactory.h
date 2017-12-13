#pragma once
#include "GuitarFactory.h"
#define SIX_STRING_GUITAR_TYPE_NAME L"SixString"

class SixStringGuitarFactory : public GuitarFactory {
public:
	SixStringGuitarFactory();
	~SixStringGuitarFactory();
	virtual Guitar* createGuitar(UCHAR instrumentNum, wstring name);
	virtual wstring getGuitarTypeName();
private:
	Note* defaultNoteFormation;
};

