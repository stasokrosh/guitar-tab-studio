#pragma once
#include "ViewComponent.h"
#include "Common.h"

class EViewComponent :
	public ViewComponent {
public:
	EViewComponent(ViewInfo* viewInfo, BeatType beatType, Callback* clickCallback);
	~EViewComponent();
	BeatType getBeatType();
private:
	BeatType beatType;
};

