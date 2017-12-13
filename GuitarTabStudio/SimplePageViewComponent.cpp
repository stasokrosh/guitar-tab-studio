#include "stdafx.h"
#include "SimplePageViewComponent.h"


SimplePageViewComponent::SimplePageViewComponent(ViewInfo* viewInfo, UCHAR num) : PageViewComponent(viewInfo, num) {
	this->tactContainer = new TactContainerViewComponent(viewInfo, viewInfo->viewConfiguration->getPageHeight(viewInfo->scale));
	this->components.push_back(this->tactContainer);
}


SimplePageViewComponent::~SimplePageViewComponent() {}
