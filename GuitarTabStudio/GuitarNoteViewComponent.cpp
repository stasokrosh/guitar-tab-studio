#include "stdafx.h"
#include "GuitarNoteViewComponent.h"


GuitarNoteViewComponent::GuitarNoteViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, CHAR* note, 
	UCHAR stringCount, BOOL selected) : ViewComponent(viewInfo, NULL, doubleClickCallback) {
	this->note = note;
	this->stringCount = stringCount;
	this->selected = selected;
	SHORT noteTextWidth = GetNoteTextFontHeight(this->viewInfo, this->stringCount);
	this->resize(noteTextWidth, noteTextWidth);
}

GuitarNoteViewComponent::~GuitarNoteViewComponent() {}

void GuitarNoteViewComponent::selfDraw(HDC hdc) {
	if (*(this->note) != -1) {
		wstring text = to_wstring(*(this->note));
		RECT rect;
		rect.top = this->getY();
		rect.left = this->getX();
		rect.bottom = this->getY() + this->getHeight();
		rect.right = this->getX() + this->getWidth();
		HFONT font = this->viewInfo->viewConfiguration->getFont(GetNoteTextFontHeight(this->viewInfo, this->stringCount));
		HANDLE oldFont = SelectObject(hdc, font);
		DrawText(hdc, text.c_str(), text.size(), &rect, DT_CENTER);
		SelectObject(hdc, oldFont);
	}
	if (this->selected) {
		HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, this->viewInfo->selectionColor);
		DrawRectangle(hdc, this->getX(), this->getY(), this->getWidth(), this->getHeight(), pen);
	}
}
