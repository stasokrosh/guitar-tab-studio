#pragma once
#include "TactTemplate.h"
#include "Guitar.h"
#include "GuitarEvent.h"

class GuitarTact : public TactTemplate<GuitarEvent> {
public:
	GuitarTact(TactInfo* tactInfo, EventFactory* eventFactory, Guitar* guitar);
	~GuitarTact();
private:
	Guitar* guitar;
};

