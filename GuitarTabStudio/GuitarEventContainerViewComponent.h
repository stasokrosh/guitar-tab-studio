#pragma once
#include "EventContainerViewComponent.h"
#include "GuitarEventViewComponent.h"

class GuitarEventContainerViewComponent :
	public EventContainerViewComponent<GuitarEventViewComponent> {
public:
	GuitarEventContainerViewComponent(ViewInfo* viewInfo, UCHAR stringCount);
	virtual void addEvents(vector<GuitarEventViewComponent*> events);
	~GuitarEventContainerViewComponent();
protected:
	virtual void selfDraw(HDC hdc);
private:
	UCHAR stringCount;

	void drawLinks(HDC hdc, vector<GuitarEventViewComponent*>* sequence, BeatTypeEx beatTypeEx, SHORT y, HPEN pen);

	void drawLink(HDC hdc, SHORT leftX, SHORT rightX, SHORT y, BeatType beatType, HPEN pen);

	void drawLink(HDC hdc, SHORT x, SHORT y, BOOL forward, BeatType beatType, HPEN pen);

	static SHORT GetLinkCount(BeatType beatType);
};

