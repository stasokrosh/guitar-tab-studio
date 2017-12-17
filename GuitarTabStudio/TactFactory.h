#pragma once
#include "Common.h"
#include "Tact.h"

class TactFactory {
public:
	virtual Tact* createTact(TactInfo* tactInfo) = 0;
};