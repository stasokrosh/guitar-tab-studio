#include "stdafx.h"
#include "SelectedEvent.h"


SelectedEvent::SelectedEvent(Callback* updateCallback) {
	this->iterator = NULL;
	this->updateCallback = updateCallback;
}


SelectedEvent::~SelectedEvent() {
	if (this->iterator != NULL) {
		delete this->iterator;
	}
}

EventIterator* SelectedEvent::getIterator(){
	return this->iterator;
}

void SelectedEvent::setIterator(EventIterator* iterator) {
	if (this->iterator != NULL) {
		delete this->iterator;
	}
	this->iterator = iterator;
}

void SelectedEvent::setIteratorAndUpdate(EventIterator* iterator) {
	if (!iterator->equal(this->iterator) && this->iterator->getEvent()->isEmpty()) {
		this->iterator->getEvent()->setPause(TRUE);
	}
	this->setIterator(iterator->copy());
	this->updateCallback->call();
}

SelectedEvent::SelectEventCallback::SelectEventCallback(SelectedEvent* selectedEvent, EventIterator* eventIterator) {
	this->selectedEvent = selectedEvent;
	this->eventIterator = eventIterator;
}

SelectedEvent::SelectEventCallback::~SelectEventCallback() {
	delete this->eventIterator;
}

void SelectedEvent::SelectEventCallback::call() {
	this->selectedEvent->setIteratorAndUpdate(this->eventIterator);
}
