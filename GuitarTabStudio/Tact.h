#pragma once
#include "Core.h"
#include <vector>

using namespace std;

class Tact {
public:
	Tact(TactDuration* pTactDuration, BOOL repriseBegin, UCHAR repriseEnd);
	~Tact();
	vector<Event*>::iterator addEvent(Event* pEvent);
	void insertEvent(vector<Event*>::iterator iterator, Event* pEvent);
	void deleteEvent(vector<Event*>::iterator iterator);
	vector<Event*>::iterator getBegin();
	vector<Event*>::iterator getEnd();
	TactValidity isValid();

	BOOL repriseBegin;
	UCHAR repriseEnd;
private: 
	vector<Event*> events;
	TactDuration* pTactDuration;
};

