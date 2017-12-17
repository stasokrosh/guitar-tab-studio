#include "stdafx.h"
#include "GuitarTactFactory.h"


GuitarTactFactory::GuitarTactFactory(Guitar* guitar) {
	this->eventFactory = new GuitarEventFactory(guitar);
	this->guitar = guitar;
}


GuitarTactFactory::~GuitarTactFactory() {
	delete this->eventFactory;
}

Tact * GuitarTactFactory::createTact(TactInfo * tactInfo) {
	return new GuitarTact(tactInfo, this->eventFactory, this->guitar);
}
