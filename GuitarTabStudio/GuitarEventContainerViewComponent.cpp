#include "stdafx.h"
#include "GuitarEventContainerViewComponent.h"


GuitarEventContainerViewComponent::GuitarEventContainerViewComponent(ViewInfo* viewInfo, UCHAR stringCount) : 
	EventContainerViewComponent<GuitarEventViewComponent>(viewInfo) {
	this->stringCount = stringCount;
}

void GuitarEventContainerViewComponent::addEvents(vector<GuitarEventViewComponent*> events) {
	EventContainerViewComponent::addEvents(events);
	USHORT tactNumFontHeight = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
	USHORT noteTextFontHeight = GetNoteTextFontHeight(viewInfo, this->stringCount);
	USHORT y = this->getY() + tactNumFontHeight - noteTextFontHeight / 2;
	for (ViewComponent* viewComponent : this->components) {
		viewComponent->move(viewComponent->getX(), y);
	}
}


GuitarEventContainerViewComponent::~GuitarEventContainerViewComponent() {}

void GuitarEventContainerViewComponent::selfDraw(HDC hdc) {
	UCHAR x;
	UCHAR beatTypeExFontHeight = GetBeatTypeExFontHeight(this->viewInfo);
	UCHAR y = this->getY() + this->getHeight() - beatTypeExFontHeight;
	HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, this->viewInfo->mainColor);
	HANDLE oldPen = SelectObject(hdc, pen);
	vector<GuitarEventViewComponent*> sequence;
	EventInfo measureEvent;
	UCHAR quaterAbsoluteBeatCount = Event::getAbsoluteBeatCount(&measureEvent);
	UCHAR eventsDurationSum = 0;
	BeatTypeEx beatTypeEx = (BeatTypeEx)-1;
	for (GuitarEventViewComponent* event : this->events) {
		x = event->getX();
		UCHAR stickHeight = GetStickHeight(this->viewInfo, event->getEvent()->getBeatType());
		if (stickHeight != 0) {
			DrawLine(hdc, x, y, x, y + stickHeight, pen);
		}
		UCHAR eventDuration = Event::getAbsoluteBeatCount(event->getEvent()->getEventInfo());
		BeatTypeEx eventBeatTypeEx = event->getEvent()->getBeatTypeEx();
		if (beatTypeEx == -1) {
			eventsDurationSum += eventDuration;
			beatTypeEx = eventBeatTypeEx;
			sequence.push_back(event);
		} else {
			if (eventsDurationSum > quaterAbsoluteBeatCount || beatTypeEx != eventBeatTypeEx) {
				this->drawLinks(hdc, &sequence, beatTypeEx, y, pen);
				sequence.clear();
				eventsDurationSum = 0;
				beatTypeEx = eventBeatTypeEx;
			}
			eventsDurationSum += eventDuration;
			sequence.push_back(event);
		}
	}
	this->drawLinks(hdc, &sequence, beatTypeEx, y, pen);
	SelectObject(hdc, oldPen);
}

void GuitarEventContainerViewComponent::drawLinks(HDC hdc, vector<GuitarEventViewComponent*>* sequence,
	BeatTypeEx beatTypeEx, UCHAR y, HPEN pen) {
	BOOL linkDrawed = FALSE;
	for (UCHAR i = 0; i < sequence->size(); i++) {
		if (i != sequence->size() - 1) {
			UCHAR beatTypeCurrent = UCHAR(sequence->at(i)->getEvent()->getBeatType());
			UCHAR beatTypeNext = UCHAR(sequence->at(i + 1)->getEvent()->getBeatType());
			if (beatTypeCurrent <= beatTypeNext) {
				this->drawLink(hdc, sequence->at(i)->getX(), sequence->at(i + 1)->getX(), y, 
					sequence->at(i)->getEvent()->getBeatType(), pen);
				linkDrawed = FALSE;
			} else {
				if (!linkDrawed) {
					this->drawLink(hdc, sequence->at(i)->getX(), y, TRUE,
						sequence->at(i + 1)->getEvent()->getBeatType(), pen);
				}
				this->drawLink(hdc, sequence->at(i)->getX(), sequence->at(i + 1)->getX(), y,
					sequence->at(i + 1)->getEvent()->getBeatType(), pen);
				linkDrawed = TRUE;
			}
		} else {
			if (!linkDrawed) {
				this->drawLink(hdc, sequence->at(i)->getX(), y, FALSE,
					sequence->at(i + 1)->getEvent()->getBeatType(), pen);
			}
		}
	}
	if (beatTypeEx != NORMAL) {
		UCHAR beatTypeExFontHeight = GetBeatTypeExFontHeight(this->viewInfo);
		RECT rect;
		rect.top = y;
		rect.bottom = y + beatTypeExFontHeight;
		rect.left = sequence->front()->getX();
		rect.right = sequence->back()->getX() + sequence->back()->getWidth();
		HFONT font = this->viewInfo->viewConfiguration->getFont(beatTypeExFontHeight);
		HANDLE oldFont = SelectObject(hdc, font);
		wstring text = to_wstring(UCHAR(beatTypeEx));
		DrawText(hdc, text.c_str(), text.size(), &rect, DT_CENTER);
		SelectObject(hdc, oldFont);
	}
}

void GuitarEventContainerViewComponent::drawLink(HDC hdc, UCHAR leftX, UCHAR rightX, UCHAR y, BeatType beatType, HPEN pen) {
	if ((UCHAR)beatType >= 8) {
		UCHAR linkCount = (UCHAR)beatType / 8;
		for (UCHAR i = 0; i < linkCount; i++) {
			y += i * 2;
			DrawLine(hdc, leftX, y, rightX, y, pen);
		}
	}
}

void GuitarEventContainerViewComponent::drawLink(HDC hdc, UCHAR x, UCHAR y, BOOL forward, BeatType beatType, HPEN pen) {
	if ((UCHAR)beatType >= 8) {
		UCHAR linkCount = (UCHAR)beatType / 8;
		UCHAR x1 = forward ? x + 2 : x - 2;
		for (UCHAR i = 0; i < linkCount; i++) {
			y += i * 2;
			DrawLine(hdc, x, y, x1, y, pen);
		}
	}
}

