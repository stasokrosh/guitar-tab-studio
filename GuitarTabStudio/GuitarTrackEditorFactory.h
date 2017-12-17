#pragma once
#include "TrackEditorFactory.h"
#include "InstrumentFactory.h"
#include "TrackTemplate.h"
#include "GuitarEvent.h"
#include "GuitarTact.h"
#include "GuitarTactFactory.h"
#include "GuitarTrackEditor.h"

class GuitarTrackEditorFactory : public TrackEditorFactory {
public:
	GuitarTrackEditorFactory(InstrumentFactory<Guitar>* instrumentFactory);
	~GuitarTrackEditorFactory();
	virtual TrackEditor* createTrackEditor(wstring instrumentName, TrackInfo trackInfo, Callback* updateCallback);
	virtual Instruments getInstrumentType();
private:
	InstrumentFactory<Guitar>* instrumentFactory;
};

