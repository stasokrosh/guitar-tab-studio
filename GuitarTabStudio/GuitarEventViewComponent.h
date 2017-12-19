#pragma once
#include "EViewComponent.h"
#include "GuitarView.h"
#include "Common.h"
#include "ChordDirections.h"
#include "GuitarNoteViewComponent.h"
#include "GuitarEvent.h"

class GuitarTrackEditor;

class GuitarEventViewComponent : public EViewComponent {
public:
	GuitarEventViewComponent(ViewInfo* viewInfo, Callback* clickCallback,
		vector<Callback*> noteCallbacks, GuitarEvent* guitarEvent, BOOL selected, CHAR stringSelected);
	~GuitarEventViewComponent();
	virtual void updateSize();
	GuitarEvent* getGuitarEvent();
protected:
	virtual void selfDraw(HDC hdc);
private:
	BOOL selected;
	GuitarEvent* guitarEvent;

	void drawPause(HDC hdc, BeatType beatType);
};

