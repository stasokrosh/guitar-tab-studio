#include "stdafx.h"
#include "GuitarInstrumentFactory.h"


GuitarInstrumentFactory::GuitarInstrumentFactory() {
	GuitarFactory* factory = new SixStringGuitarFactory();
	this->factories.insert(pair<wstring, GuitarFactory*>(factory->getGuitarTypeName(), factory));
	factory = new BassGuitarFactory();
	this->factories.insert(pair<wstring, GuitarFactory*>(factory->getGuitarTypeName(), factory));
}

BOOL GuitarInstrumentFactory::initialize() {
	wifstream stream;
	try {
		stream.open(GUITAR_DATA_FILE_NAME);
		while (!stream.eof()) {
			wstring guitarRecord;
			ReadLine(&stream, &guitarRecord);
			vector<wstring> parts = Divide(guitarRecord);
			if (parts.size() != 3) {
				return FALSE;
			}
			if (!this->guitarTypeExists(parts.at(1))) {
				return FALSE;
			}
			UCHAR instrumentNum = stoi(parts.at(2));
			this->guitarsData.insert(pair<wstring, pair<wstring, UCHAR>>(parts.at(0), pair<wstring, UCHAR>(parts.at(1), instrumentNum)));
		}
		stream.close();
		return TRUE;
	}
	catch (exception e) {
		if (stream.is_open()) {
			stream.close();
		}
		return FALSE;
	}
}

Guitar * GuitarInstrumentFactory::createInstrument(wstring name) {
	map<wstring, pair<wstring, UCHAR>>::iterator iData = this->guitarsData.find(name);
	if (iData == this->guitarsData.end()) {
		return NULL;
	} else {
		wstring guitarType = ((*iData).second).first;
		GuitarFactory* factory = (*(this->factories.find(guitarType))).second;
		return factory->createGuitar((*iData).second.second, name);
	}
}

vector<wstring> GuitarInstrumentFactory::getInstrumentNames() {
	vector<wstring> names;
	for (pair<wstring, pair<wstring, UCHAR>> name : this->guitarsData) {
		names.push_back(name.first);
	}
	return names;
}

BOOL GuitarInstrumentFactory::guitarTypeExists(wstring guitarType) {
	for (pair<wstring, GuitarFactory*> factory : this->factories) {
		if (factory.first == guitarType) {
			return TRUE;
		}
	}
	return FALSE;
}


GuitarInstrumentFactory::~GuitarInstrumentFactory() {
	for (pair<wstring, GuitarFactory*> factory : this->factories) {
		delete factory.second;
	}
}
