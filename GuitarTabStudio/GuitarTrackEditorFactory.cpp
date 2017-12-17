#include "stdafx.h"
#include "GuitarTrackEditorFactory.h"


GuitarTrackEditorFactory::GuitarTrackEditorFactory(InstrumentFactory<Guitar>* instrumentFactory) {
	this->instrumentFactory = instrumentFactory;
}


GuitarTrackEditorFactory::~GuitarTrackEditorFactory() {
	delete this->instrumentFactory;
}

TrackEditor * GuitarTrackEditorFactory::createTrackEditor(wstring instrumentName, TrackInfo trackInfo, Callback* updateCallback) {
	Guitar* guitar = this->instrumentFactory->createInstrument(instrumentName);
	TactFactory* tactFactory = new GuitarTactFactory(guitar);
	TrackTemplate<GuitarTact>* track = new TrackTemplate<GuitarTact>(trackInfo, guitar, tactFactory);
	return new GuitarTrackEditor(track, guitar, updateCallback);
}

Instruments GuitarTrackEditorFactory::getInstrumentType() {
	return GUITAR;
}
