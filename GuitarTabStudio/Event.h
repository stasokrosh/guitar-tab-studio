#pragma once
#include "Core.h"
#include "Tact.h"

#include "ViewComponent.h"
#include "View.h"

#include "MidiEvent.h"


class Event {
public:	
	Event(EventInfo eventInfo, Tact* tact);
	UCHAR getAbsoluteBeatCount();
	virtual MidiEvent* getMidiEvent(UCHAR channel, UCHAR* velocity) = 0;
	virtual ViewComponent* getViewComponent(ViewInfo viewInfo) = 0;
	virtual BOOL isEmpty() = 0;
	Tact* getTact();
	EventInfo* getEventInfo();
private:
	EventInfo eventInfo;
	Tact* tact;
};

