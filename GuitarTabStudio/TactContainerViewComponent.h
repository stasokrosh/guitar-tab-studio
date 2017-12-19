#pragma once
#include "ViewComponent.h"

class TactContainerViewComponent : public ViewComponent {
public:
	TactContainerViewComponent(ViewInfo* viewInfo, SHORT height);
	~TactContainerViewComponent();
	void addTacts(vector<ViewComponent*>* tacts);
};

