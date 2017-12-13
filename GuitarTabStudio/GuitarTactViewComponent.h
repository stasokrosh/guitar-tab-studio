#pragma once
#include "TactViewComponent.h"
#include "GuitarEventViewComponent.h"
#include "GuitarEventContainerViewComponent.h"
#include "GuitarView.h"

class GuitarTactViewComponent : public TactViewComponent<GuitarEventViewComponent> {
public:
	GuitarTactViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, 
		USHORT num, UCHAR stringCount, Tact* tact);
	void setSelected(BOOL selected);
	void setLast(BOOL last);
	~GuitarTactViewComponent();
protected:
	virtual void selfDraw(HDC hdc);
	Tact* tact;
private:
	UCHAR stringCount;
	BOOL selected;
	BOOL last;
};

