#include "stdafx.h"
#include "EventContainerViewComponent.h"

template<class T>
EventContainerViewComponent<T>::EventContainerViewComponent(ViewInfo* viewInfo) : ViewComponent(viewInfo, NULL, NULL) {
	this->resize(0, viewInfo->viewConfiguration->getTactHeight(viewInfo->scale));
}

template<class T>
void EventContainerViewComponent<T>::addEvents(vector<T*> events) {
	this->components.clear();
	this->events.clear();
	USHORT tactBorder = this->viewInfo->viewConfiguration->getTactBorder(this->viewInfo->scale);
	USHORT x = tactBorder + this->getX();
	for (T* viewComponent : events) {
		this->events.push_back(viewComponent);
		this->components.push_back(viewComponent);
		viewComponent->move(x, viewComponent->getY());
		x += viewComponent->getWidth() + this->viewInfo->viewConfiguration->getEventInterval(this->viewInfo->scale,
			viewComponent->getEvent()->getBeatType());
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
