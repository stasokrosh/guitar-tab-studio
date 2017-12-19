#pragma once
#include "InstrumentFactory.h"
#include "Guitar.h"
#include "GuitarFactory.h"
#include "SixStringGuitarFactory.h" 
#include "BassGuitarFactory.h"
#include <map>
#include "Serialization.h"
using namespace std;

#define GUITAR_DATA_FILE_NAME "C:\\guitars.ini"

class GuitarInstrumentFactory : public InstrumentFactory<Guitar> {
public:
	GuitarInstrumentFactory();
	~GuitarInstrumentFactory();
	virtual BOOL initialize();
	virtual Guitar* createInstrument(wstring name);
	virtual vector<wstring> getInstrumentNames();
private:
	map<wstring, pair<wstring, UCHAR>> guitarsData;
	map<wstring, GuitarFactory*> factories;

	BOOL guitarTypeExists(wstring guitarType);
};

