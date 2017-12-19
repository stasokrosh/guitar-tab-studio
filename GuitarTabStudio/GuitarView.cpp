#include "stdafx.h"
#include "GuitarView.h"

SHORT GetTabHeight(ViewInfo * viewInfo) {
	SHORT tactHeight = viewInfo->viewConfiguration->getTactHeight(viewInfo->scale);
	SHORT tactNumFontHeight = viewInfo->viewConfiguration->getTactNumFontHeight(viewInfo->scale);
	return tactHeight / 2 - tactNumFontHeight;
}

SHORT GetLineInterval(ViewInfo * viewInfo, int stringCount) {
	SHORT tabHeight = GetTabHeight(viewInfo);
	return tabHeight / (stringCount - 1);
}

SHORT GetNoteTextFontHeight(ViewInfo* viewInfo, int stringCount) {
	return GetLineInterval(viewInfo, stringCount) - 1;
}

SHORT GetBeatTypeExFontHeight(ViewInfo * viewInfo) {
	return GetTabHeight(viewInfo) / 3;
}

SHORT GetStickHeight(ViewInfo * viewInfo, BeatType beatType) {
	switch (beatType) {
	case  WHOLE: {
		return 0;
	} break;
	case HALF: {
		return GetBeatTypeExFontHeight(viewInfo);
	} break;
	default: {
		return GetBeatTypeExFontHeight(viewInfo) * 2;
	}
	}
}

SHORT GetTactDuarationFontHeight(ViewInfo * viewInfo) {
	return GetTabHeight(viewInfo) / 2 - 2;
}

void DrawArrow(HDC hdc, SHORT x1, SHORT y1, SHORT x2, SHORT y2,HPEN pen, BOOL forward) {
	DrawLine(hdc, x1, y1, x2, y2, pen);
	if (forward) {
		DrawLine(hdc, x2, y2, x2 - 2, y2 - 3, pen);
		DrawLine(hdc, x2, y2, x2 + 2, y2 - 3, pen);
	} else {
		DrawLine(hdc, x1, y1, x1 - 2, y1 + 3, pen);
		DrawLine(hdc, x1, y1, x1 + 2, y1 + 3, pen);
	}
}
