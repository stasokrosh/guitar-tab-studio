#pragma once
#include "FactoryOfTrackEditorFactory.h"
#include "model.h" 
#include "GuitarTrackEditorFactory.h"
#include "GuitarInstrumentFactory.h"
#include <map>

using namespace std;

class FactoryOfTrackEditorFactoryImpl : public FactoryOfTrackEditorFactory {
public:
	FactoryOfTrackEditorFactoryImpl();
	~FactoryOfTrackEditorFactoryImpl();
	BOOL initialize();
	virtual TrackEditorFactory* getTrackEditorFactory(Instruments instrumentType);
private:
	map<Instruments, TrackEditorFactory*> factories;
};

