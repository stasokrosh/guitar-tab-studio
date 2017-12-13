#pragma once
#include "Guitar.h"
#include <string>

using namespace std;

class GuitarFactory {
public:
	virtual Guitar* createGuitar(UCHAR instrumentNum, wstring name) = 0;
	virtual wstring getGuitarTypeName() = 0;
};