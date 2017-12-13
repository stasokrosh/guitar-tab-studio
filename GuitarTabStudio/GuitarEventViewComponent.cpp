#include "stdafx.h"
#include "GuitarEventViewComponent.h"


GuitarEventViewComponent::GuitarEventViewComponent(ViewInfo* viewInfo, Callback* clickCallback, GuitarEvent* event, 
	NotesEditor* notesEditor, GuitarTrackEditor* trackEditor) : EventViewComponent(viewInfo, clickCallback, event) {
	this->selected = false;
	this->stringCount = event->getStringCount();
	this->notesSelected = new BOOL[stringCount]{ FALSE };
	USHORT y = 0;
	USHORT lineInterval = GetLineInterval(viewInfo, stringCount);
	for (UCHAR i = 0; i < stringCount; i++) {
		Callback* callback = new SelectGuitarNoteCallback(notesEditor, trackEditor, event, i);
		GuitarNoteViewComponent* noteViewComponent = new GuitarNoteViewComponent(viewInfo, callback, event->getNote(i),stringCount, &(this->notesSelected[i]));
		this->components.push_back(noteViewComponent);
		noteViewComponent->move(this->getX(), y);
		y += lineInterval;
	}
	updateSize();
}


GuitarEventViewComponent::~GuitarEventViewComponent() {
	delete this->notesSelected;
}

void GuitarEventViewComponent::setSelected(BOOL selected) {
	this->selected = selected;
}

void GuitarEventViewComponent::setNoteSelected(BOOL selected, UCHAR stringNum) {
	this->notesSelected[stringNum] = selected;
}

void GuitarEventViewComponent::deselectAllNotes() {
	for (UCHAR i = 0; i < this->stringCount; i++) {
		this->setNoteSelected(FALSE, i);
	}
}

void GuitarEventViewComponent::updateSize() {
	USHORT height = GetTabHeight(this->viewInfo);
	USHORT maxWidth = 0;
	for (ViewComponent* viewComponent : this->components) {
		if (viewComponent->getWidth() > maxWidth) {
			maxWidth = viewComponent->getWidth();
		}
	}
	this->resize(maxWidth, height);
}

void GuitarEventViewComponent::selfDraw(HDC hdc) {
	if (this->selected) {
		HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, this->viewInfo->selectionColor);
		DrawRectangle(hdc, this->getX(), this->getY(), this->getWidth(), this->getHeight());
	}
	if (this->getEvent()->isPause()) {
		this->drawPause(hdc, this->getEvent()->getBeatType());
	}
}

void GuitarEventViewComponent::drawPause(HDC hdc, BeatType beatType) {

}
