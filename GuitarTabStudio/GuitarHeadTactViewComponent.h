#pragma once
#include "GuitarTactViewComponent.h"
#include "GuitarView.h"
#include "Midi.h"

class GuitarHeadTactViewComponent : public GuitarTactViewComponent {
public:
	GuitarHeadTactViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, Guitar* guitar, Tact* tact);
	~GuitarHeadTactViewComponent();
	virtual void resize(USHORT width, USHORT height);
	virtual void addEvents(vector<GuitarEventViewComponent*> events);
protected:
	virtual void selfDraw(HDC hdc);
private:
	Guitar* guitar;
};

