#pragma once
#include "TrackEditor.h"
#include "TrackTemplate.h"
#include "GuitarTact.h"
#include "GuitarEvent.h"
#include "HeaderViewComponent.h"
#include "HeaderPageViewComponent.h"
#include "SimplePageViewComponent.h"

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
private:
	TrackViewComponent* trackViewComponent;
	TrackTemplate<GuitarTact>* guitarTrack;
	Guitar* guitar;
	BOOL stringSelected;
	UCHAR selectedString; 

	GuitarEvent* getSelectedGuitarEvent();
};

