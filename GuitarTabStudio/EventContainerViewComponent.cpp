#include "stdafx.h"
#include "EventContainerViewComponent.h"

template<class T>
EventContainerViewComponent<T>::EventContainerViewComponent(ViewInfo* viewInfo) : ViewComponent(viewInfo, NULL, NULL) {
	this->resize(0, viewInfo->viewConfiguration->getTactHeight(viewInfo->scale));
}

template<class T>
void EventContainerViewComponent<T>::addEvents(vector<T*> events) {
	this->components.clear();
	USHORT tactBorder = this->viewInfo->viewConfiguration->getTactBorder(this->viewInfo->scale);
	USHORT x = tactBorder + this->getX();
	for (EventViewComponent* eventViewComponent : events) {
		this->events.push_back(eventViewCommponent);
		this->components.push_back(eventViewComponent);
		eventViewComponent->move(x, eventViewComponent->getY());
		x += eventViewComponent->getWidth() + this->viewInfo->viewConfiguration->getEventInterval(this->viewInfo->scale,
			eventViewComponent->getEvent()->getBeatType());
	}
	this->resize(x - this->getX(), this->getY());
}

template<class T>
void EventContainerViewComponent<T>::resize(USHORT width, USHORT height) {
	USHORT deltaWidth = width - this->getWidth();
	if (deltaWidth > 0) {
		USHORT addedDelta = deltaWidth / this->components.size();
		for (int i = 1; i < this->components.size(); i++) {
			ViewComponent* viewComponent = this->components.at(i);
			viewComponent->move(viewComponent->getX() + addedDelta * i, viewComponent->getY());
		}
	}
	ViewComponent::resize(width, height);
}

template<class T>
EventContainerViewComponent<T>::~EventContainerViewComponent() {}
