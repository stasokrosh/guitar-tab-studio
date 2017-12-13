#pragma once
#include "TactTemplate.h"
#include "GuitarTactViewComponent.h"
#include "GuitarHeadTactViewComponent.h"

class GuitarTact : public TactTemplate<GuitarEvent> {
public:
	GuitarTact(TactInfo* tactInfo, Track* track, EventFactory* eventFactory, Guitar* guitar);
	GuitarTactViewComponent* getViewComponent(ViewInfo* viewInfo, USHORT num);
	~GuitarTact();
private:
	Guitar* guitar;
};

