#pragma once
#include "TactViewComponent.h"
#include "GuitarEventViewComponent.h"
#include "GuitarEventContainerViewComponent.h"
#include "GuitarView.h"

class GuitarTactViewComponent : public TactViewComponent<GuitarEventViewComponent> {
public:
	GuitarTactViewComponent(ViewInfo* viewInfo, USHORT num, UCHAR stringCount, TactInfo* tactInfo, BOOL valid);
	~GuitarTactViewComponent();
	void setLast();
protected:
	virtual void selfDraw(HDC hdc);
	UCHAR stringCount;
	BOOL last;
	TactInfo* tactInfo;
	BOOL valid;
};

