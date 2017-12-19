#include "stdafx.h"
#include "GuitarEventContainerViewComponent.h"


GuitarEventContainerViewComponent::GuitarEventContainerViewComponent(ViewInfo* viewInfo, UCHAR stringCount) : 
	EventContainerViewComponent<GuitarEventViewComponent>(viewInfo) {
	this->stringCount = stringCount;
}

void GuitarEventContainerViewComponent::addEvents(vector<GuitarEventViewComponent*> events) {
	EventContainerViewComponent::addEvents(events);
	SHORT tactNumFontHeight = this->viewInfo->viewConfiguration->getTactNumFontHeight(this->viewInfo->scale);
	SHORT noteTextFontHeight = GetNoteTextFontHeight(viewInfo, this->stringCount);
	SHORT y = this->getY() + tactNumFontHeight - noteTextFontHeight / 2;
	for (ViewComponent* viewComponent : this->components) {
		viewComponent->move(viewComponent->getX(), y);
	}
}


GuitarEventContainerViewComponent::~GuitarEventContainerViewComponent() {}

void GuitarEventContainerViewComponent::selfDraw(HDC hdc) {
	SHORT x;
	SHORT beatTypeExFontHeight = GetBeatTypeExFontHeight(this->viewInfo);
	SHORT y = this->getY() + this->getHeight() - beatTypeExFontHeight - 2;
	HPEN pen = this->viewInfo->viewConfiguration->getPen(LINE_STYLE, LINE_WIDTH, this->viewInfo->mainColor);
	HANDLE oldPen = SelectObject(hdc, pen);
	vector<GuitarEventViewComponent*> sequence;
	EventInfo measureEvent;
	SHORT quaterAbsoluteBeatCount = Event::getAbsoluteBeatCount(&measureEvent);
	SHORT eventsDurationSum = 0;
	BeatTypeEx beatTypeEx = (BeatTypeEx)-1;
	for (GuitarEventViewComponent* event : this->events) {
		x = event->getX() + event->getWidth() / 2;
		BeatType beatType = event->getGuitarEvent()->getBeatType();
		SHORT stickHeight = GetStickHeight(this->viewInfo, beatType);
		if (stickHeight != 0) {
			DrawLine(hdc, x, y, x, y - stickHeight, pen);
		}
		SHORT dotCount = event->getGuitarEvent()->getDotCount();
		if (dotCount > 0) {
			SHORT dotHeight = y - 4 * (GetLinkCount(beatType) + 1);
			for (SHORT j = 1; j <= dotCount; j++) {
				DrawRectangle(hdc, x + 2 * j, dotHeight, 1, 1, pen);
			}
		}
		SHORT eventDuration = Event::getAbsoluteBeatCount(event->getGuitarEvent()->getEventInfo());
		BeatTypeEx eventBeatTypeEx = event->getGuitarEvent()->getBeatTypeEx();
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
	BeatTypeEx beatTypeEx, SHORT y, HPEN pen) {
	BOOL linkDrawed = FALSE;
	for (SHORT i = 0; i < sequence->size(); i++) {
		GuitarEventViewComponent* first = sequence->at(i);
		if (i != sequence->size() - 1) {
			GuitarEventViewComponent* second = sequence->at(i + 1);
			SHORT beatTypeCurrent = SHORT(first->getGuitarEvent()->getBeatType());
			SHORT beatTypeNext = SHORT(second->getGuitarEvent()->getBeatType());
			if (beatTypeCurrent <= beatTypeNext) {
				this->drawLink(hdc, first->getX() + first->getWidth() / 2, second->getX() + second->getWidth() / 2,
					y, first->getGuitarEvent()->getBeatType(), pen);
				linkDrawed = FALSE;
			} else {
				if (!linkDrawed) {
					this->drawLink(hdc, first->getX() + first->getWidth() / 2, y, TRUE,
						first->getGuitarEvent()->getBeatType(), pen);
				}
				this->drawLink(hdc, first->getX() + first->getWidth() / 2, second->getX() + second->getWidth() / 2, y,
					second->getGuitarEvent()->getBeatType(), pen);
				linkDrawed = TRUE;
			}
		} else {
			if (!linkDrawed) {
					this->drawLink(hdc, first->getX() + first->getWidth() / 2, y, this->components.size() == 1,
						first->getGuitarEvent()->getBeatType(), pen);
			}
		}
	}
	if (beatTypeEx != NORMAL) {
		SHORT beatTypeExFontHeight = GetBeatTypeExFontHeight(this->viewInfo);
		RECT rect;
		rect.top = y + 2;
		rect.bottom = y + beatTypeExFontHeight;
		rect.left = sequence->front()->getX();
		rect.right = sequence->back()->getX() + sequence->back()->getWidth();
		HFONT font = this->viewInfo->viewConfiguration->getFont(beatTypeExFontHeight);
		HANDLE oldFont = SelectObject(hdc, font);
		wstring text = to_wstring(SHORT(beatTypeEx));
		DrawText(hdc, text.c_str(), text.size(), &rect, DT_CENTER);
		SelectObject(hdc, oldFont);
	}
}

void GuitarEventContainerViewComponent::drawLink(HDC hdc, SHORT leftX, SHORT rightX, SHORT y, BeatType beatType, HPEN pen) {
	if ((SHORT)beatType >= 8) {
		SHORT linkCount = GetLinkCount(beatType);
		for (SHORT i = 0; i < linkCount; i++) {
			DrawRectangle(hdc, leftX, y, rightX - leftX, 1, pen);
			y -= 4;
		}
	}
}

void GuitarEventContainerViewComponent::drawLink(HDC hdc, SHORT x, SHORT y, BOOL forward, BeatType beatType, HPEN pen) {
	if ((SHORT)beatType >= 8) {
		SHORT linkCount = GetLinkCount(beatType);
		SHORT x1 = forward ? x + 5 : x - 5;
		for (SHORT i = 0; i < linkCount; i++) {
			DrawRectangle(hdc, x, y, x1 - x, 1, pen);
			y -= 4;
		}
	}
}

SHORT GuitarEventContainerViewComponent::GetLinkCount(BeatType beatType) {
	if (beatType < 8) {
		return 0;
	}
	beatType = (BeatType)(beatType / 8);
	SHORT shiftedBeat = 1;
	SHORT result = 1;
	while (shiftedBeat != beatType) {
		result++;
		shiftedBeat <<= 1;
	}
	return result;
}

