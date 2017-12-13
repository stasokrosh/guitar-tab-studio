#pragma once
#include "ViewComponent.h"
#include "PageViewComponent.h"

class TrackViewComponent :
	public ViewComponent {
public:
	TrackViewComponent(ViewInfo* viewInfo);
	~TrackViewComponent();
	void addPages(vector<PageViewComponent*> pages);
	ViewComponent* getSelectedViewComponent();
	void setSelectedViewComponent(ViewComponent* viewComponent);
private:
	ViewComponent* selectedComponent;
};

