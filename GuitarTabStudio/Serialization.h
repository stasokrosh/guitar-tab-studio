#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Common.h"
#include "Instrument.h"

#define EXTENSION L".gt"

using namespace std;

void WriteLine(wofstream* stream, wstring line);

void WriteCompositionInfo(wofstream* stream, CompositionInfo* compositionInfo);

void WriteTrackInfo(wofstream* stream, TrackInfo* trackInfo);

void WriteTactInfo(wofstream* stream, TactInfo* tactInfo);

void WriteInstrument(wofstream* stream, Instrument* instrument);

void WriteEventInfo(wofstream* stream, EventInfo* eventInfo);

void ReadLine(wifstream* stream, wstring* line);

vector<wstring> Divide(wstring text);

BOOL ReadCompositionInfo(wifstream* stream, CompositionInfo* compositionInfo);

BOOL ReadTrackInfo(wifstream* stream, TrackInfo* trackInfo);

BOOL ReadTactInfo(wifstream* stream, TactInfo* tactInfo);

BOOL ReadInstrumentInfo(wifstream* stream, wstring* name, Instruments* instrumentType);

BOOL ReadEventInfo(wifstream* stream, EventInfo* eventInfo);

vector<wstring> ReadVector(wifstream* stream);