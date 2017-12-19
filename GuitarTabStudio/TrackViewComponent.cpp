#include "stdafx.h"
#include "TrackViewComponent.h"


TrackViewComponent::TrackViewComponent(ViewInfo* viewInfo) : ViewComponent(viewInfo, NULL, NULL) {
	this->resize(viewInfo->viewConfiguration->getPageWidth(viewInfo->scale), 0);
}

void TrackViewComponent::addPages(vector<PageViewComponent*> pages) {
	SHORT x = this->getX();
	SHORT y = this->getY();
	SHORT pageInterval = this->viewInfo->viewConfiguration->getPageInterval(this->viewInfo->scale);
	for (PageViewComponent* page : pages) {
		y += pageInterval;
		this->components.push_back(page);
		page->move(x, y);
		y += page->getHeight();
	}
	this->resize(this->getWidth(), y - this->getY());
}

ViewComponent * TrackViewComponent::getSelectedViewComponent() {
	return this->selectedComponent;
}

void TrackViewComponent::setSelectedViewComponent(ViewComponent * viewComponent) {
	this->selectedComponent = viewComponent;
}


TrackViewComponent::~TrackViewComponent() {}
