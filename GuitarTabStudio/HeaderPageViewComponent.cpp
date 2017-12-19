#include "stdafx.h"
#include "HeaderPageViewComponent.h"


HeaderPageViewComponent::HeaderPageViewComponent(ViewInfo* viewInfo, HeaderViewComponent* headerViewComponent) : 
	PageViewComponent(viewInfo, 1) {
	this->headerViewComponent = headerViewComponent;
	this->tactContainer = new TactContainerViewComponent(viewInfo, this->getHeight() - this->headerViewComponent->getHeight());
	this->tactContainer->move(this->getX(), this->getY() + headerViewComponent->getHeight());
	this->components.push_back(headerViewComponent);
	this->components.push_back(this->tactContainer);
}


HeaderPageViewComponent::~HeaderPageViewComponent() { }
