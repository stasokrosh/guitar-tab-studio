#include "stdafx.h"
#include "TactIterator.h"

BOOL TactIterator::equal(TactIterator * eventIterator) {
	return this->getTact() == eventIterator->getTact();
}
