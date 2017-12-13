#include "stdafx.h"
#include "EventViewComponent.h"


EventViewComponent::EventViewComponent(ViewInfo* viewInfo, Callback* clickCallback, Event* event) :
	ViewComponent(viewInfo, clickCallback, NULL){
	this->event = event;
}


EventViewComponent::~EventViewComponent() {}

Event * EventViewComponent::getEvent() {
	return this->event;
}
