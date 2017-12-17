#include "stdafx.h"
#include "GuitarTact.h"


GuitarTact::GuitarTact(TactInfo* tactInfo, EventFactory* eventFactory, Guitar* guitar) : 
	TactTemplate<GuitarEvent>(tactInfo, eventFactory) {
	this->guitar = guitar;
}

GuitarTact::~GuitarTact() {}
