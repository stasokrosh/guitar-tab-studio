#include "stdafx.h"
#include "GuitarEventFactory.h"

GuitarEventFactory::GuitarEventFactory(Guitar * guitar) {
	this->guitar = guitar;
}

GuitarEventFactory::~GuitarEventFactory() {}

Event * GuitarEventFactory::createEvent(EventInfo eventInfo) {
	return new GuitarEvent(eventInfo, this->guitar, NONE);
}
