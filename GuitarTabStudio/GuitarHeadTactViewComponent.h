#pragma once
#include "GuitarTactViewComponent.h"
#include "GuitarView.h"
#include "GuitarEventViewComponent.h"

class GuitarHeadTactViewComponent : public GuitarTactViewComponent {
public:
	GuitarHeadTactViewComponent(ViewInfo* viewInfo, Guitar* guitar, TactInfo* tactInfo, BOOL valid);
	~GuitarHeadTactViewComponent();
	virtual void resize(SHORT width, SHORT height);
	virtual void addEvents(vector<GuitarEventViewComponent*> events);
protected:
	virtual void selfDraw(HDC hdc);
private:
	Guitar* guitar;
};

