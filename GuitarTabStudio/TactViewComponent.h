#pragma once
#include "ViewComponent.h"
#include "NotesEditor.h" 
#include "EventContainerViewComponent.h"
#include <string>

using namespace std;

template<class T>
class TactViewComponent : public ViewComponent {
public:
	TactViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, SHORT num) : ViewComponent(viewInfo, NULL, NULL) {
		this->resize(0, viewInfo->viewConfiguration->getTactHeight(viewInfo->scale));
		this->num = num;
	}
	virtual void addEvents(vector<T*> events) {
		this->eventContainer->addEvents(events);
		this->resize(this->eventContainer->getWidth(), this->getHeight());
	}
	virtual void resize(SHORT width, SHORT height) {
		ViewComponent::resize(width, height);
		if (this->eventContainer != NULL) {
			this->eventContainer->resize(this->getWidth(), this->getHeight());
		}
	}
protected:
	EventContainerViewComponent<T>* eventContainer;
	SHORT num;

	virtual void selfDraw(HDC hdc) {
		SHORT height = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
		SHORT width = height * 4;
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
};

