#pragma once
#include "PageViewComponent.h"
#include "HeaderViewComponent.h"

class HeaderPageViewComponent : public PageViewComponent {
public:
	HeaderPageViewComponent(ViewInfo* viewInfo, HeaderViewComponent* headerViewComponent);
	~HeaderPageViewComponent();
private:
	HeaderViewComponent* headerViewComponent;
};

