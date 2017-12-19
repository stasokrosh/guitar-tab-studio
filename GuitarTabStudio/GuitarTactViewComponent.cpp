#include "stdafx.h"
#include "GuitarTactViewComponent.h"


GuitarTactViewComponent::GuitarTactViewComponent(ViewInfo* viewInfo, SHORT num, UCHAR stringCount, 
	TactInfo* tactInfo, BOOL valid) : TactViewComponent<GuitarEventViewComponent>(viewInfo, NULL, num) {
	this->stringCount = stringCount;
	this->eventContainer = new GuitarEventContainerViewComponent(viewInfo, stringCount);
	this->components.push_back(eventContainer);
	this->last = FALSE;
	this->tactInfo = tactInfo;
	this->valid = valid;
}


GuitarTactViewComponent::~GuitarTactViewComponent() {}

void GuitarTactViewComponent::setLast() {
	this->last = TRUE;
}

void GuitarTactViewComponent::selfDraw(HDC hdc) {
	SHORT tactNumFontHeight = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
	SHORT tabHeight = GetTabHeight(this->viewInfo);
	SHORT lineInterval = GetLineInterval(viewInfo, this->stringCount);
	SHORT y = this->getY() + tactNumFontHeight;
	COLORREF color;
	if (this->valid) {
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
	DrawLine(hdc, this->getX(), this->getY() + tactNumFontHeight, this->getX(), 
		this->getY() + tactNumFontHeight + lineInterval * (this->stringCount - 1), pen);
	DrawLine(hdc, this->getX() + this->getWidth(), this->getY() + tactNumFontHeight, this->getX() + this->getWidth(), 
		this->getY() + tactNumFontHeight + lineInterval * (this->stringCount - 1) , pen);
	if (this->last || this->tactInfo->repriseEnd > 1) {
		DrawLine(hdc, this->getX() + this->getWidth() - 2, this->getY() + tactNumFontHeight, this->getX() + this->getWidth() - 2,
			this->getY() + tactNumFontHeight + lineInterval * (this->stringCount - 1), pen);
	}
	if (this->tactInfo->repriseBegin) {
		DrawLine(hdc, this->getX() + 2, this->getY() + tactNumFontHeight, this->getX() + 2, this->getY() + tactNumFontHeight + tabHeight, pen);
	}
	SelectObject(hdc, oldPen);
	TactViewComponent<GuitarEventViewComponent>::selfDraw(hdc);
}
