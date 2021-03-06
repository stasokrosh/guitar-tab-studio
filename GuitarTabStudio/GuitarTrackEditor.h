#pragma once
#include "TrackEditor.h"
#include "TrackTemplate.h"
#include "GuitarTact.h"
#include "GuitarEvent.h"
#include "HeaderViewComponent.h"
#include "HeaderPageViewComponent.h"
#include "SimplePageViewComponent.h"
#include "GuitarTactViewComponent.h"
#include "GuitarHeadTactViewComponent.h"
#include "GuitarEventViewComponent.h"
#include "Serialization.h"
#include "GuitarMidiEvent.h"

class GuitarTrackEditor : public TrackEditor {
public:
	GuitarTrackEditor(TrackTemplate<GuitarTact>* guitarTrack, Guitar* guitar, Callback* updateCallback);
	~GuitarTrackEditor();
	virtual void moveUp();
	virtual void moveDown();
	void selectString(UCHAR num);
	void deselectString();
	virtual TrackViewComponent* getTrackViewComponent(ViewInfo* viewInfo, CompositionInfo* compositionInfo);
	virtual void Write(wofstream* stream);
	virtual BOOL Load(wifstream* stream, vector<TactInfo*>* tacts);
	virtual void preparePlaying();
	virtual void moveForward();
	virtual void moveBackwards();
	GuitarEvent* getSelectedGuitarEvent();
	Guitar* getGuitar();
	void deleteSymbol();
	void addSymbol(UCHAR num);
	void setChordDirection(ChordDirections chordDirection);
protected:
	virtual MidiEvent* getMidiEvent(Event* event, UCHAR channel, Callback* selectEventCallback);
private:
	TrackViewComponent* trackViewComponent;
	TrackTemplate<GuitarTact>* guitarTrack;
	Guitar* guitar;
	BOOL stringSelected;
	UCHAR selectedString; 

	GuitarTactViewComponent* getTactViewComponent(ViewInfo* viewInfo, SHORT num, GuitarTact* tact, Tact* selectedTact);
	GuitarEventViewComponent* getEventViewComponent(ViewInfo* viewInfo, EventIteratorTemplate<GuitarEvent>* iterator);
	static void WriteGuitarEvent(wofstream* stream, GuitarEvent* guitarEvent);
	static BOOL ReadGuitarEvent(wifstream* stream, GuitarEvent* guitarEvent);
	static void WriteGuitar(wofstream* stream, Guitar* guitar);
	static BOOL ReadGuitar(wifstream* stream, Guitar* guitar);

	class SelectStringCallback : public Callback {
	public:
		SelectStringCallback(Callback* selectEventCallback, UCHAR stringNum,
			GuitarTrackEditor* trackEditor);
		~SelectStringCallback();
		void call();
	private:
		UCHAR stringNum;
		GuitarTrackEditor* trackEditor;
		Callback* selectEventCallback;
	};

	class SelectNoteCallback : public Callback {
	public:
		SelectNoteCallback(Callback* selectEventCallback, GuitarTrackEditor* trackEditor);
		~SelectNoteCallback();
		void call();
	private:
		GuitarTrackEditor* trackEditor;
		Callback* selectEventCallback;
	};
};

