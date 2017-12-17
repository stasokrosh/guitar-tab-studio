#pragma once
#include "View.h"
#include "Common.h"

class ViewConfiguration {
public:
	ViewConfiguration();
	~ViewConfiguration();
	USHORT getPageWidth(Scale scale);
	USHORT getPageHeight(Scale scale); 
	USHORT getPageInterval(Scale scale);
	USHORT getPageNumFontHeight(Scale scale);
	USHORT getTactHeight(Scale scale);
	USHORT getEventInterval(Scale scale, BeatType beatType);
	USHORT getHorizontalBorder(Scale scale);
	USHORT getVerticalBorder(Scale scale);
	USHORT getTactBorder(Scale scale);
	USHORT getTactNumFontHeight(Scale scale);
	USHORT getCompositionNameFontHeight(Scale scale);
	USHORT getArtistNameFontHeight(Scale scale);
	USHORT getTrackInfoFontHeight(Scale scale);
	USHORT getInformationIntervalHeight(Scale scale);
	HFONT getFont(UCHAR fontHeight);
	HPEN getPen(int style, int width, COLORREF color);
	HBRUSH getSolidBrush(COLORREF color);
};

