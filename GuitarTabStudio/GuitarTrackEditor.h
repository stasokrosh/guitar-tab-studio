#pragma once
#include "TrackEditor.h"
#include "TrackTemplate.h"
#include "GuitarTact.h"
#include "GuitarEvent.h"
#include "HeaderViewComponent.h"
#include "HeaderPageViewComponent.h"
#include "SimplePageViewComponent.h"
#include "Serialization.h"

class GuitarTrackEditor : public TrackEditor {
public:
	GuitarTrackEditor(TrackTemplate<GuitarTact>* guitarTrack, Guitar* guitar, NotesEditor* NotesEditor);
	~GuitarTrackEditor();
	virtual void moveUp();
	virtual void moveDown();
	void selectString(UCHAR num);
	void deselectString();
	virtual TrackViewComponent* getTrackViewComponent(ViewInfo* viewInfo);
	void setCapo(UCHAR capo);
	virtual void Write(wofstream* stream);
	virtual BOOL Load(wifstream* stream, vector<TactInfo*>* tacts, TactIterator** selectedTact,
		EventIterator** selectedEvent);
private:
	TrackViewComponent* trackViewComponent;
	TrackTemplate<GuitarTact>* guitarTrack;
	Guitar* guitar;
	BOOL stringSelected;
	UCHAR selectedString; 

	GuitarEvent* getSelectedGuitarEvent();
	static void WriteGuitarEvent(wofstream* stream, GuitarEvent* guitarEvent);
	static BOOL ReadGuitarEvent(wifstream* stream, GuitarEvent* guitarEvent);
	static void WriteGuitar(wofstream* stream, Guitar* guitar);
	static BOOL ReadGuitar(wifstream* stream, Guitar* guitar);
};

