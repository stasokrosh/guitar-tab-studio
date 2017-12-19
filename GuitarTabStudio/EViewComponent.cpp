#include "stdafx.h"
#include "EViewComponent.h"


EViewComponent::EViewComponent(ViewInfo* viewInfo, BeatType beatType, Callback* clickCallback) : 
	ViewComponent(viewInfo, clickCallback, NULL) {
	this->beatType = beatType;
}


EViewComponent::~EViewComponent() {}

BeatType EViewComponent::getBeatType() {
	return this->beatType;
}
