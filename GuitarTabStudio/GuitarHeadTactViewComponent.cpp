#include "stdafx.h"
#include "GuitarHeadTactViewComponent.h"


GuitarHeadTactViewComponent::GuitarHeadTactViewComponent(ViewInfo* viewInfo, Guitar* guitar, TactInfo* tactInfo, BOOL valid) :
	GuitarTactViewComponent(viewInfo, 1, guitar->getStringCount(), tactInfo, valid) {
	this->guitar = guitar;
}

GuitarHeadTactViewComponent::~GuitarHeadTactViewComponent() {}

void GuitarHeadTactViewComponent::resize(USHORT width, USHORT height) {
	ViewComponent::resize(width, height);
	USHORT tabHeight = GetTabHeight(this->viewInfo);
	this->eventContainer->resize(width - tabHeight, this->getHeight());
}

void GuitarHeadTactViewComponent::addEvents(vector<GuitarEventViewComponent*> events) {
	this->eventContainer->addEvents(events);
	USHORT tabHeight = GetTabHeight(this->viewInfo);
	this->resize(this->eventContainer->getWidth() + tabHeight, this->getHeight());
}

void GuitarHeadTactViewComponent::selfDraw(HDC hdc) {
	GuitarTactViewComponent::selfDraw(hdc);
	USHORT tabHeight = GetTabHeight(this->viewInfo);
	HFONT font = this->viewInfo->viewConfiguration->getFont(tabHeight / 2);
	HANDLE oldFont = SelectObject(hdc, font);
	wstring text = to_wstring(this->tactInfo->tactDuration->beatCount);
	RECT rect;
	rect.top = this->getY();
	rect.left = this->getX();
	rect.bottom = this->getY() + tabHeight / 2;
	rect.right = this->getX() + tabHeight;
	DrawText(hdc, text.c_str(), text.size(), &rect, DT_CENTER);
	text = to_wstring(this->tactInfo->tactDuration->beatType);
	rect.top = rect.bottom;
	rect.bottom = rect.bottom + tabHeight / 2;
	DrawText(hdc, text.c_str(), text.size(), &rect, DT_CENTER);
	USHORT tactNumFontHeight = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
	USHORT noteTextFontHeight = GetNoteTextFontHeight(viewInfo, this->guitar->getStringCount());
	USHORT lineInterval = GetLineInterval(viewInfo, this->guitar->getStringCount());
	font = this->viewInfo->viewConfiguration->getFont(noteTextFontHeight);
	SelectObject(hdc, font);
	rect.top = this->getY() + tactNumFontHeight - noteTextFontHeight / 2;
	rect.left = this->getX() - noteTextFontHeight * 2;
	rect.bottom = rect.top + lineInterval;
	rect.right = this->getX();
	for (UCHAR i = 0; i < this->guitar->getStringCount(); i++) {
		text = NoteToWstring(this->guitar->getString(i)->frequency);
		DrawText(hdc, text.c_str(), text.size(), &rect, DT_LEFT);
		rect.top += lineInterval;
		rect.bottom += lineInterval;
	}
	rect.top = this->getY();
	rect.left = this->getX();
	rect.bottom = this->getY() + tactNumFontHeight;
	rect.right = this->getX() + this->getWidth();
	font = this->viewInfo->viewConfiguration->getFont(tactNumFontHeight);
	SelectObject(hdc, font);
	text = L"Capo: ";
	if (this->guitar->getCapo() == 0) {
		text += L"no capo";
	} else {
		text += to_wstring(this->guitar->getCapo());
	}
	DrawText(hdc, text.c_str(), text.size(), &rect, DT_LEFT);
	SelectObject(hdc, oldFont);
}
