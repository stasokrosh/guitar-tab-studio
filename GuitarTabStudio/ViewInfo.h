#pragma once
#include "Windows.h"
#include "View.h"
#include "ViewConfiguration.h"

struct ViewInfo {
	Scale scale;
	COLORREF mainColor;
	COLORREF mainBackgroundColor;
	COLORREF selectionColor;
	COLORREF selectionBackgroundColor;
	COLORREF errorColor;
	ViewConfiguration* viewConfiguration;
};

