#pragma once
#include "ViewComponent.h"
#include "TactContainerViewComponent.h"
#include "Drawing.h"

class PageViewComponent : public ViewComponent {
public:
	PageViewComponent(ViewInfo* viewInfo, UCHAR num);
	~PageViewComponent();
	TactContainerViewComponent* getTactContainer();
protected:
	TactContainerViewComponent* tactContainer;
	virtual void selfDraw(HDC hdc);

private:
	UCHAR num;
};

