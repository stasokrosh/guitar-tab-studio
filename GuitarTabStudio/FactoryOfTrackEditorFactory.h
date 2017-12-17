#pragma once
#include "Common.h"
#include "TrackEditorFactory.h"

class FactoryOfTrackEditorFactory {
public:
	virtual TrackEditorFactory* getTrackEditorFactory(Instruments instrumentType) = 0;
};