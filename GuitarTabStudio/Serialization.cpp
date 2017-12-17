#include "stdafx.h"
#include "Serialization.h"

void WriteLine(wofstream * stream, wstring line) {
	line += L"\n";
	(*stream).write(line.c_str(), line.size());
}

void WriteCompositionInfo(wofstream * stream, CompositionInfo * compositionInfo) {
	wstring line = compositionInfo->name + L" " + compositionInfo->author + L" " +
		to_wstring(compositionInfo->tactDuration.beatCount) + L" " + to_wstring(compositionInfo->tactDuration.beatType) +
		to_wstring(compositionInfo->tempo);
	WriteLine(stream, line);
}

void WriteTrackInfo(wofstream * stream, TrackInfo * trackInfo) {
	wstring line = to_wstring(trackInfo->velocity) + L" " + trackInfo->name;
	WriteLine(stream, line);
}


void WriteTactInfo(wofstream * stream, TactInfo * tactInfo) {
	wstring line = to_wstring(tactInfo->repriseBegin) + L" " + to_wstring(tactInfo->repriseEnd);
	WriteLine(stream, line);
}

void WriteInstrument(wofstream * stream, Instrument * instrument) {
	wstring line = instrument->getName() + L" " + to_wstring(instrument->getInstrumentType());
	WriteLine(stream, line);
}

void WriteEventInfo(wofstream * stream, EventInfo* eventInfo) {
	wstring line = to_wstring(eventInfo->beatType) + L" " + to_wstring(eventInfo->beatTypeEx) + L" " +
		to_wstring(eventInfo->dotCount) + L" " + to_wstring(eventInfo->pause);
	WriteLine(stream, line);
}

void ReadLine(wifstream * stream, wstring * line) {
	getline(*stream, *line, L'\n');
}

vector<wstring> Divide(wstring text) {
	vector<wstring> parts;
	wstringstream sstream;
	while (!sstream.eof()) {
		wstring part;
		getline(sstream, part, L' ');
		parts.push_back(part);
	}
	return parts;
}

BOOL ReadCompositionInfo(wifstream * stream, CompositionInfo * compositionInfo) {
	vector<wstring> parts = ReadVector(stream);
	if (parts.size() != 5) {
		return FALSE;
	}
	compositionInfo->name = parts.at(0);
	compositionInfo->author = parts.at(1);
	compositionInfo->tactDuration.beatCount = stoi(parts.at(2));
	compositionInfo->tactDuration.beatType = (BeatType)stoi(parts.at(3));
	compositionInfo->tempo = (UCHAR)stoi(parts.at(4));
	return TRUE;
}

BOOL ReadTrackInfo(wifstream * stream, TrackInfo * trackInfo) {
	vector<wstring> parts = ReadVector(stream);
	if (parts.size() != 2) {
		return FALSE;
	}
	trackInfo->velocity = (UCHAR)stoi(parts.at(0));
	trackInfo->name = parts.at(1);
	return TRUE;
}

BOOL ReadTactInfo(wifstream * stream, TactInfo * tactInfo) {
	vector<wstring> parts = ReadVector(stream);
	if (parts.size() != 2) {
		return FALSE;
	}
	tactInfo->repriseBegin = (BOOL)stoi(parts.at(0));
	tactInfo->repriseEnd = (UCHAR)stoi(parts.at(1));
	return TRUE;
}

BOOL ReadInstrumentInfo(wifstream * stream, wstring * name, Instruments * instrumentType) {
	vector<wstring> parts = ReadVector(stream);
	if (parts.size() != 2) {
		return FALSE;
	}
	*name = parts.at(0);
	*instrumentType = (Instruments)stoi(parts.at(1));
	return TRUE;
}

BOOL ReadEventInfo(wifstream * stream, EventInfo * eventInfo) {
	vector<wstring> parts = ReadVector(stream);
	if (parts.size() != 4) {
		return FALSE;
	}
	eventInfo->beatType = (BeatType)stoi(parts.at(0));
	eventInfo->beatTypeEx = (BeatTypeEx)stoi(parts.at(1));
	eventInfo->dotCount = (UCHAR)stoi(parts.at(2));
	eventInfo->pause = (BOOL)stoi(parts.at(3));
	return TRUE;
}

vector<wstring> ReadVector(wifstream * stream) {
	wstring line;
	ReadLine(stream, &line);
	return Divide(line);
}
