#include "stdafx.h"
#include "GuitarTactViewComponent.h"


GuitarTactViewComponent::GuitarTactViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback,
	USHORT num, UCHAR stringCount, Tact* tact) : TactViewComponent<GuitarEventViewComponent>(viewInfo, doubleClickCallback, num) {
	this->selected = FALSE;
	this->stringCount = stringCount;
	this->tact = tact;
	this->last = FALSE;
	this->eventContainer = new GuitarEventContainerViewComponent(viewInfo, stringCount);
	this->components.push_back(eventContainer);
}

void GuitarTactViewComponent::setSelected(BOOL selected) {
	this->selected = selected;
}

void GuitarTactViewComponent::setLast(BOOL last) {
	this->last = last;
}

GuitarTactViewComponent::~GuitarTactViewComponent() {}

void GuitarTactViewComponent::selfDraw(HDC hdc) {
	if (this->selected) {
		HBRUSH brush = CreateSolidBrush(this->viewInfo->selectionBackgroundColor);
		FillRectangle(hdc, this->getX, this->getY(), this->getWidth(), this->getHeight(), brush);
		DeleteObject(brush);
	}
	USHORT tactNumFontHeight = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
	USHORT tabHeight = GetTabHeight(this->viewInfo);
	USHORT lineInterval = GetLineInterval(viewInfo, this->stringCount);
	USHORT y = this->getY() + tactNumFontHeight;
	COLORREF color;
	if (this->tact->isValid()) {
		color = this->viewInfo->mainColor;
	} else {
		color = this->viewInfo->errorColor;
	}
	HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, color);
	HANDLE oldPen = SelectObject(hdc, pen);
	for (UCHAR i = 0; i < this->stringCount; i++) {
		DrawLine(hdc, this->getX(), y, this->getX() + this->getWidth(), y, pen);
		y += lineInterval;
	}
	DrawLine(hdc, this->getX(), this->getY() + tactNumFontHeight, this->getX(), this->getY() + tactNumFontHeight + tabHeight, pen);
	DrawLine(hdc, this->getX() + this->getWidth(), this->getY() + tactNumFontHeight, this->getX() + this->getWidth(), 
		this->getY() + tactNumFontHeight + tabHeight, pen);
	if (this->last || this->tact->getTactInfo()->repriseEnd > 1) {
		DrawLine(hdc, this->getX() + this->getWidth() - 2, this->getY() + tactNumFontHeight, this->getX() + this->getWidth() - 2,
			this->getY() + tactNumFontHeight + tabHeight, pen);
	}
	if (this->tact->getTactInfo()->repriseBegin) {
		DrawLine(hdc, this->getX() + 2, this->getY() + tactNumFontHeight, this->getX() + 2, this->getY() + tactNumFontHeight + tabHeight, pen);
	}
	SelectObject(hdc, oldPen);
}
