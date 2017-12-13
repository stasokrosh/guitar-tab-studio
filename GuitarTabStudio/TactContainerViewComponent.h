#pragma once
#include "ViewComponent.h"

class TactContainerViewComponent : public ViewComponent {
public:
	TactContainerViewComponent(ViewInfo* viewInfo, USHORT height);
	~TactContainerViewComponent();
	void addTacts(vector<ViewComponent*>* tacts);
};

