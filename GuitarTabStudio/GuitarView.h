#pragma once
#include "Windows.h"
#include "View.h"

#define LINE_STYLE PS_SOLID
#define LINE_WIDTH 1

USHORT GetTabHeight(ViewInfo* viewInfo);

USHORT GetLineInterval(ViewInfo* viewInfo, int stringCount);

USHORT GetNoteTextFontHeight(ViewInfo* viewInfo, int stringCount);

USHORT GetBeatTypeExFontHeight(ViewInfo* viewInfo);

USHORT GetStickHeight(ViewInfo* viewInfo, BeatType beatType);
