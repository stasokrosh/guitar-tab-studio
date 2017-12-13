#include "stdafx.h"
#include "GuitarEventFactory.h"

GuitarEventFactory::GuitarEventFactory(Guitar * guitar) {
	this->guitar = guitar;
}

GuitarEventFactory::~GuitarEventFactory() {}

Event * GuitarEventFactory::createEvent(EventInfo eventInfo, Tact * tact) {
	return new GuitarEvent(eventInfo, tact, this->guitar, NONE);
}
