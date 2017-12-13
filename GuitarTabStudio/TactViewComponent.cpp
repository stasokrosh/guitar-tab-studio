#include "stdafx.h"
#include "TactViewComponent.h"

template<class T>
TactViewComponent<T>::TactViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, USHORT num) : 
	ViewComponent(viewInfo, NULL, NULL) {
	this->resize(0, viewInfo->viewConfiguration->getTactHeight(viewInfo->scale));
	this->num = num;
}

template<class T>
TactViewComponent<T>::~TactViewComponent() { }

template<class T>
void TactViewComponent<T>::addEvents(vector<T*> events) {
	this->eventContainer->addEvents(events);
	this->resize(this->eventContainer->getWidth(), this->getHeight());
}

template<class T>
void TactViewComponent<T>::resize(USHORT width, USHORT height) {
	ViewComponent::resize(width, height);
	this->eventContainer->resize(this->getWidth(), this->getHeight());
}

template<class T>
void TactViewComponent<T>::selfDraw(HDC hdc) {
	USHORT height = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
	USHORT width = height * 4;
	HFONT font = this->viewInfo->viewConfiguration->getFont(height);
	wstring text = to_wstring(this->num);
	RECT rect;
	rect.left = this->getX() + this->getWidth() - width;
	rect.top = this->getY();
	rect.bottom = this->getY() + height;
	rect.right = this->getX() + this->getWidth();
	HANDLE oldFont = SelectObject(hdc, font);
	DrawText(hdc, text.c_str(), text.size(), &rect, DT_RIGHT);
	SelectObject(hdc, oldFont);
}

