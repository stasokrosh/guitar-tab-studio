#include "stdafx.h"
#include "GuitarEventViewComponent.h"


GuitarEventViewComponent::GuitarEventViewComponent(ViewInfo* viewInfo, Callback* clickCallback, vector<Callback*> noteCallbacks, 
	GuitarEvent* guitarEvent, BOOL selected, CHAR stringSelected) : ViewComponent(viewInfo, clickCallback, NULL) {
	this->guitarEvent = guitarEvent;
	this->selected = false;
	UCHAR stringCount = guitarEvent->getStringCount();
	USHORT y = 0;
	USHORT lineInterval = GetLineInterval(viewInfo, stringCount);
	for (UCHAR i = 0; i < stringCount; i++) {
		GuitarNoteViewComponent* noteViewComponent = new GuitarNoteViewComponent(viewInfo, noteCallbacks.at(i),
			guitarEvent->getNote(i),stringCount, i == stringSelected);
		this->components.push_back(noteViewComponent);
		noteViewComponent->move(this->getX(), y);
		y += lineInterval;
	}
	updateSize();
}


GuitarEventViewComponent::~GuitarEventViewComponent() {
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
	}
	ChordDirections chordDirection = this->guitarEvent->getChordDirection();
	if (chordDirection != NONE) {
		HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, this->viewInfo->mainColor);
		DrawArrow(hdc, this->getX() + this->getWidth() + 3, this->getY(), this->getX() + this->getWidth() + 3, 
			this->getY() + this->getHeight(), pen, chordDirection == DOWN);
	}
}

void GuitarEventViewComponent::drawPause(HDC hdc, BeatType beatType) {
	UCHAR lineInterval = GetLineInterval(this->viewInfo, this->guitarEvent->getStringCount());
	UCHAR tactNumFontHeight = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
	UCHAR y = tactNumFontHeight + lineInterval * this->guitarEvent->getStringCount() / 2;
	UCHAR x = this->getX() + this->getWidth() / 4;
	HBRUSH brush = this->viewInfo->viewConfiguration->getSolidBrush(this->viewInfo->mainColor);
	FillRectangle(hdc, x, y, this->getWidth() / 2, lineInterval / 2, brush);
}
