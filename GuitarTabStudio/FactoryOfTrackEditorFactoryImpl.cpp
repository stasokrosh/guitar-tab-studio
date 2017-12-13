#include "stdafx.h"
#include "FactoryOfTrackEditorFactoryImpl.h"


FactoryOfTrackEditorFactoryImpl::FactoryOfTrackEditorFactoryImpl() {}


FactoryOfTrackEditorFactoryImpl::~FactoryOfTrackEditorFactoryImpl() {
	for (pair<Instruments, TrackEditorFactory*> factory : this->factories) {
		delete factory.second;
	}
}

BOOL FactoryOfTrackEditorFactoryImpl::initialize() {
	GuitarInstrumentFactory* guitarInstrumentFactory = new GuitarInstrumentFactory();
	if (!guitarInstrumentFactory->initialize()) {
		return FALSE;
	}
	GuitarTrackEditorFactory* guitarTrackEditorFactory = new GuitarTrackEditorFactory(guitarInstrumentFactory);
	this->factories.insert(pair<Instruments, TrackEditorFactory*>(guitarTrackEditorFactory->getInstrumentType(),
		guitarTrackEditorFactory));
	return TRUE;
}

TrackEditorFactory * FactoryOfTrackEditorFactoryImpl::getTrackEditorFactory(Instruments instrumentType) {
	map<Instruments, TrackEditorFactory*>::iterator iterator = this->factories.find(instrumentType);
	if (iterator == this->factories.end()) {
		return NULL;
	} else {
		return (*iterator).second;
	}
}
