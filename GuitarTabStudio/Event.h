#pragma once
#include "Common.h"
#include "MidiEvent.h"
#include "Callback.h"

class Event {
public:	
	Event(EventInfo eventInfo);
	virtual ~Event();
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
	virtual MidiEvent* getMidiEvent(UCHAR channel, UCHAR* velocity,Callback* changeNoteCallback) = 0;
	virtual void setPause(BOOL pause);
	virtual BOOL isEmpty() = 0;
	virtual void setEmpty() = 0;
protected:
	EventInfo eventInfo;
};

