#pragma once
#include "Composition.h"
#include "Event.h"
#include "TrackEditor.h"

#define DEFAULT_BEAT_TYPE QUATER
#define DEFAULT_BEAT_TYPE_EX NORMAL
#define DEFAULT_DOT_COUNT 0

class NotesEditor {
public:
	NotesEditor();
	~NotesEditor();
	void CreateComposition(CompositionInfo compositionInfo);
	void LoadComposition(string fileName);
	void SaveCompositionAs(string fileName);
	void SaveComposition();

	void setBeatType(BeatType beatType);
	void setBeatTypeEx(BeatTypeEx beatTypeEx);
	void setDotCount(UCHAR dotCount);
	void setCompositionInfo(CompositionInfo compositionInfo);
	void setTrackName(string trackName);

	BeatType getBeatType();
	BeatTypeEx getBeatTypeEx();
	UCHAR getDotCount();
	string getFileName();
	CompositionInfo getCompositionInfo();
	Instrument* getInstrument();
	string getTrackName();

	AddTact
private:
	void initializeTrackEditors();
	void clearTrackEditorsVector();
	void selectTrackEditor(TrackEditor* trackEditor);
	Track* getSelectedTrack();

	EventInfo eventInfo;
	Composition* composition;
	string fileName;
	vector<TrackEditor*> trackEditors;
	TrackEditor* selectedTrackEditor;
};

