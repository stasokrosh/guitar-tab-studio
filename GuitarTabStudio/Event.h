#pragma once
#include "Model.h"
#include "Tact.h"

#include "MidiEvent.h"


class Event {
public:	
	Event(EventInfo eventInfo, Tact* tact);
	Tact* getTact();
	EventInfo* getEventInfo();
	BeatType getBeatType();
	BeatTypeEx getBeatTypeEx();
	UCHAR getDotCount();
	BOOL isPause();
	void setBeatType(BeatType beatType);
	void setBeatTypeEx(BeatTypeEx beatTypeEx);
	void setDotCount(UCHAR dotCount);
	static UCHAR getAbsoluteBeatCount(EventInfo* eventInfo);
	UCHAR getAbsoluteBeatCount();
	virtual MidiEvent* getMidiEvent(UCHAR channel, UCHAR* velocity) = 0;
	virtual void setPause(BOOL pause);
	virtual BOOL isEmpty() = 0;
	virtual void setEmpty() = 0;
protected:
	EventInfo eventInfo;
	Tact* tact;
};

