#include "stdafx.h"
#include "GuitarTact.h"


GuitarTact::GuitarTact(TactInfo* tactInfo, Track* track, EventFactory* eventFactory, Guitar* guitar) : 
	TactTemplate<GuitarEvent>(tactInfo, track, eventFactory) {
	this->guitar = guitar;
}

GuitarTactViewComponent * GuitarTact::getViewComponent(ViewInfo * viewInfo, USHORT num) {
	if (num == 1) {
		return new GuitarHeadTactViewComponent(viewInfo, NULL, this->guitar, this);
	} else {
		return new GuitarTactViewComponent(viewInfo, NULL, num, this->guitar->getStringCount(), this);
	}
}


GuitarTact::~GuitarTact() {}
