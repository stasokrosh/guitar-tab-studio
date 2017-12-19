#include "stdafx.h"
#include "GuitarEventViewComponent.h"


GuitarEventViewComponent::GuitarEventViewComponent(ViewInfo* viewInfo, Callback* clickCallback, vector<Callback*> noteCallbacks, 
	GuitarEvent* guitarEvent, BOOL selected, CHAR stringSelected) : EViewComponent(viewInfo, guitarEvent->getBeatType(), clickCallback) {
	this->guitarEvent = guitarEvent;
	this->selected = selected && stringSelected == -1;
	UCHAR stringCount = guitarEvent->getStringCount();
	SHORT y = this->getY() + 1;
	SHORT lineInterval = GetLineInterval(viewInfo, stringCount);
	for (UCHAR i = 0; i < stringCount; i++) {
		GuitarNoteViewComponent* noteViewComponent = new GuitarNoteViewComponent(viewInfo, noteCallbacks.at(i),
			guitarEvent->getNote(i),stringCount, i == stringSelected && selected);
		this->components.push_back(noteViewComponent);
		noteViewComponent->move(this->getX(), y);
		y += lineInterval;
	}
	updateSize();
}


GuitarEventViewComponent::~GuitarEventViewComponent() {
}

void GuitarEventViewComponent::updateSize() {
	SHORT height = GetLineInterval(this->viewInfo, this->guitarEvent->getStringCount()) * this->guitarEvent->getStringCount();
	SHORT width;
	if (this->guitarEvent->isPause()) {
		width = GetNoteTextFontHeight(this->viewInfo, this->guitarEvent->getStringCount()) * 2;
	} else {
		width = GetNoteTextFontHeight(this->viewInfo, this->guitarEvent->getStringCount());
	}
	this->resize(width, height);
}

GuitarEvent* GuitarEventViewComponent::getGuitarEvent() {
	return this->guitarEvent;
}

void GuitarEventViewComponent::selfDraw(HDC hdc) {
	if (this->selected) {
		HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, this->viewInfo->selectionColor);
		DrawRectangle(hdc, this->getX(), this->getY(), this->getWidth(), this->getHeight(), pen);
	}
	if (this->guitarEvent->isPause()) {
		this->drawPause(hdc, this->guitarEvent->getBeatType());
	} else {
		ChordDirections chordDirection = this->guitarEvent->getChordDirection();
		if (chordDirection != NONE) {
			HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, this->viewInfo->mainColor);
			DrawArrow(hdc, this->getX() + this->getWidth() + 3, this->getY(), this->getX() + this->getWidth() + 3,
				this->getY() + this->getHeight(), pen, chordDirection == DOWN);
		}
	}
}

void GuitarEventViewComponent::drawPause(HDC hdc, BeatType beatType) {
	SHORT lineInterval = GetLineInterval(this->viewInfo, this->guitarEvent->getStringCount());
	SHORT y = this->getY() + -lineInterval / 2 + lineInterval * this->guitarEvent->getStringCount() / 2;
	SHORT x = this->getX() + this->getWidth() / 4;
	HBRUSH brush = this->viewInfo->viewConfiguration->getSolidBrush(this->viewInfo->mainColor);
	FillRectangle(hdc, x, y, this->getWidth() / 2, lineInterval / 2, brush);
}
