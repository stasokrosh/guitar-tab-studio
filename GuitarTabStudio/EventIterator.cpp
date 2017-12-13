#include "stdafx.h"
#include "EventIterator.h"

BOOL EventIterator::equal(EventIterator * eventIterator) {
	return this->getEvent() == eventIterator->getEvent();
}
