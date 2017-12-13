#pragma once
#include "EventViewComponent.h"
#include "GuitarEvent.h"
#include "GuitarView.h"
#include "GuitarNoteViewComponent.h"
#include "NotesEditor.h"
#include "SelectGuitarNoteCallback.h"

class GuitarEventViewComponent : public EventViewComponent {
public:
	GuitarEventViewComponent(ViewInfo* viewInfo, Callback* clickCallback, GuitarEvent* event,
		NotesEditor* notesEditor, GuitarTrackEditor* trackEditor);
	~GuitarEventViewComponent();
	void setSelected(BOOL selected);
	void setNoteSelected(BOOL selected, UCHAR stringNum);
	void deselectAllNotes();
	virtual void updateSize();
protected:
	virtual void selfDraw(HDC hdc);
private:
	BOOL selected;
	BOOL* notesSelected;
	UCHAR stringCount;
	void drawPause(HDC hdc, BeatType beatType);
};

