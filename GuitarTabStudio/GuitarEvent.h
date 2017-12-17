#pragma once
#include "Event.h"
#include "Guitar.h"
#include "ChordDirections.h"

class GuitarEvent : public Event {
public:
	GuitarEvent(EventInfo eventInfo, Guitar* guitar, ChordDirections chordDirection);
	~GuitarEvent();
    virtual BOOL isEmpty();
	virtual void setEmpty();
	virtual void setPause(BOOL pause);
	CHAR* getNote(int stringNum);
	ChordDirections getChordDirection();
	void setChordDirection(ChordDirections chordDirection);
	UCHAR getStringCount();
private:
	ChordDirections chordDirection;
	CHAR* notes;
	Guitar* guitar;
};

