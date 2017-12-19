#pragma once
#include "Windows.h"
#include "ViewInfo.h"
#include "Drawing.h"

#define LINE_STYLE PS_SOLID
#define LINE_WIDTH 1

SHORT GetTabHeight(ViewInfo* viewInfo);

SHORT GetLineInterval(ViewInfo* viewInfo, int stringCount);

SHORT GetNoteTextFontHeight(ViewInfo* viewInfo, int stringCount);

SHORT GetBeatTypeExFontHeight(ViewInfo* viewInfo);

SHORT GetStickHeight(ViewInfo* viewInfo, BeatType beatType);

SHORT GetTactDuarationFontHeight(ViewInfo* viewInfo);

void DrawArrow(HDC hdc, SHORT x1, SHORT y1, SHORT x2, SHORT y2, HPEN pen, BOOL forward);
