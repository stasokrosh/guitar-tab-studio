#pragma once
#include "Tact.h"

class TactFactory {
public:
	virtual Tact* createTact(TactInfo* tactInfo, Track* track) = 0;
};