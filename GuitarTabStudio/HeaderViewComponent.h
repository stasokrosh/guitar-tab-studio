#pragma once
#include "ViewComponent.h"
#include "Instrument.h"
#include "Common.h"
#include <string>

using namespace std;

class HeaderViewComponent : public ViewComponent {
public:
	HeaderViewComponent(ViewInfo* viewInfo, CompositionInfo* compositionInfo, TrackInfo* trackInfo, Instrument* instrument);
	~HeaderViewComponent();
protected:
	CompositionInfo* compositionInfo;
	TrackInfo* trackInfo;
	Instrument* instrument;

	virtual void selfDraw(HDC hdc);
};

