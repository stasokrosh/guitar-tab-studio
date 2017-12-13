#pragma once
#include "Windows.h"
#include "ViewConfiguration.h"

enum Scale {
	MIN = 75,
	MDM = 100,
	HGH = 125
};

struct ViewInfo {
	Scale scale;
	COLORREF mainColor;
	COLORREF mainBackgroundColor;
	COLORREF selectionColor;
	COLORREF selectionBackgroundColor;
	COLORREF errorColor;
	ViewConfiguration* viewConfiguration;
};


void DrawLine(HDC hdc, USHORT x1, USHORT y1, USHORT x2, USHORT y2, HPEN pen);

void FillRectangle(HDC hdc, USHORT x, USHORT y, USHORT width, USHORT height, HBRUSH brush);

void DrawRectangle(HDC hdc, USHORT x, USHORT y, USHORT width, USHORT height, HPEN pen);