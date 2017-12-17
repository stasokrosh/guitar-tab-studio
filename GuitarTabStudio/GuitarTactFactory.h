#pragma once
#include "TactFactory.h"
#include "GuitarEventFactory.h"
#include "GuitarTact.h"

class GuitarTactFactory : public TactFactory {
public:
	GuitarTactFactory(Guitar* guitar);
	~GuitarTactFactory();
	virtual Tact* createTact(TactInfo* tactInfo);
private:
	GuitarEventFactory* eventFactory;
	Guitar* guitar;
};

