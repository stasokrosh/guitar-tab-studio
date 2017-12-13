#include "stdafx.h"
#include "GuitarView.h"

USHORT GetTabHeight(ViewInfo * viewInfo) {
	USHORT tactHeight = viewInfo->viewConfiguration->getTactHeight(viewInfo->scale);
	USHORT tactNumFontHeight = viewInfo->viewConfiguration->getTactNumFontHeight(viewInfo->scale);
	return tactHeight / 2 - tactNumFontHeight;
}

USHORT GetLineInterval(ViewInfo * viewInfo, int stringCount) {
	USHORT tabHeight = GetTabHeight(viewInfo);
	return tabHeight / (stringCount - 1);
}

USHORT GetNoteTextFontHeight(ViewInfo* viewInfo, int stringCount) {
	return GetLineInterval(viewInfo, stringCount) - 1;
}

USHORT GetBeatTypeExFontHeight(ViewInfo * viewInfo) {
	return GetTabHeight(viewInfo) / 4;
}

USHORT GetStickHeight(ViewInfo * viewInfo, BeatType beatType) {
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
