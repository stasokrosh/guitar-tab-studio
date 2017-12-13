#pragma once
#include "TrackEditorFactory.h"


class FactoryOfTrackEditorFactory {
public:
	virtual TrackEditorFactory* getTrackEditorFactory(Instruments instrumentType) = 0;
};