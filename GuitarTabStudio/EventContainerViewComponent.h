#pragma once
#include "ViewComponent.h"
#include <vector>

using namespace std;

template<class T>
class EventContainerViewComponent : public ViewComponent {
public:
	EventContainerViewComponent(ViewInfo* viewInfo) : ViewComponent(viewInfo, NULL, NULL) {
		this->resize(0, viewInfo->viewConfiguration->getTactHeight(viewInfo->scale));
	}
	virtual void resize(SHORT width, SHORT height) {
		SHORT deltaWidth = width - this->getWidth();
		if (deltaWidth > 0) {
			SHORT addedDelta = deltaWidth / this->components.size();
			for (int i = 1; i < this->components.size(); i++) {
				ViewComponent* viewComponent = this->components.at(i);
				viewComponent->move(viewComponent->getX() + addedDelta * i, viewComponent->getY());
			}
		}
		ViewComponent::resize(width, height);
	}
	virtual void addEvents(vector<T*> events) {
		this->components.clear();
		this->events.clear();
		SHORT tactBorder = this->viewInfo->viewConfiguration->getTactBorder(this->viewInfo->scale);
		SHORT x = tactBorder + this->getX();
		for (T* viewComponent : events) {
			this->events.push_back(viewComponent);
			this->components.push_back(viewComponent);
			viewComponent->move(x, viewComponent->getY());
			x += viewComponent->getWidth() + 
				this->viewInfo->viewConfiguration->getEventInterval(this->viewInfo->scale, viewComponent->getBeatType());
		}
		this->width = x - this->getX();
	}
protected:
	vector<T*> events;
};

