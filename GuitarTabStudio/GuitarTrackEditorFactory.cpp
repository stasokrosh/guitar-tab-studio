#include "stdafx.h"
#include "GuitarTrackEditorFactory.h"


GuitarTrackEditorFactory::GuitarTrackEditorFactory(InstrumentFactory<Guitar>* instrumentFactory) {
	this->instrumentFactory = instrumentFactory;
}


GuitarTrackEditorFactory::~GuitarTrackEditorFactory() {
	delete this->instrumentFactory
}

TrackEditor * GuitarTrackEditorFactory::createTrackEditor(wstring instrumentName, TrackInfo trackInfo, NotesEditor * notesEditor) {
	Guitar* guitar = this->instrumentFactory->createInstrument(instrumentName);
	TactFactory* tactFactory = new GuitarTactFactory(guitar);
	TrackTemplate<GuitarTact>* track = new TrackTemplate<GuitarTact>(trackInfo, guitar, tactFactory);
	return new GuitarTrackEditor(track, guitar, notesEditor);
}

Instruments GuitarTrackEditorFactory::getInstrumentType() {
	return GUITAR;
}
