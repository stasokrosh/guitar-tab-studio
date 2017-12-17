#pragma once
#include "EventIterator.h"
#include "Callback.h"

class SelectedEvent {
public:
	SelectedEvent(Callback* updateCallback);
	~SelectedEvent();
	EventIterator* getIterator();
	void setIterator(EventIterator* iterator);
	void setIteratorAndUpdate(EventIterator* iterator);
	class SelectEventCallback : public Callback {
	public:
		SelectEventCallback(SelectedEvent* selectedEvent, EventIterator* eventIterator);
		~SelectEventCallback();
		void call();
	private:
		SelectedEvent* selectedEvent;
		EventIterator* eventIterator;
	};
private:
	EventIterator* iterator;
	Callback* updateCallback;
};

