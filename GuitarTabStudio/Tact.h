#pragma once
#include "Core.h"
#include <vector>

using namespace std;

class Tact : public Sequence<Event>{
public:
	Tact(TactDuration* pTactDuration, BOOL repriseBegin, UCHAR repriseEnd);
	~Tact();
	TactValidity isValid();

	BOOL repriseBegin;
	UCHAR repriseEnd;
	TactDuration* pTactDuration;
};

