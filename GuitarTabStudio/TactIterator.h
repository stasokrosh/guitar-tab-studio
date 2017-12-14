#pragma once

#include "Tact.h"

class TactIterator {
public:
	virtual Tact* getTact() = 0;
	virtual void deleteTact() = 0;
	virtual void moveForward() = 0;
	virtual void moveBackwards() = 0;
	virtual void insertTact(TactInfo* tactInfo) = 0;
	virtual BOOL equal(TactIterator* eventIterator);
	virtual BOOL isLast() = 0;
	virtual BOOL isFirst() = 0;
	virtual USHORT getPosition() = 0;
};