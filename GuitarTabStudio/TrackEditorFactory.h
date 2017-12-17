#pragma once
#include "Common.h"
#include "TrackEditor.h"
#include <string>

using namespace std;


class TrackEditorFactory {
public:
	virtual TrackEditor* createTrackEditor(wstring instrumentName, TrackInfo trackInfo, Callback* updateCallback) = 0;
	virtual Instruments getInstrumentType() = 0;
};