#pragma once
#include "View.h"
#include "Common.h"
#include <map>

using namespace std;

#define DEFAULT_PAGE_WIDTH 800
#define DEFAULT_PAGE_HEIGHT DEFAULT_PAGE_WIDTH * 297 / 210

class ViewConfiguration {
public:
	ViewConfiguration();
	~ViewConfiguration();
	SHORT getPageWidth(Scale scale);
	SHORT getPageHeight(Scale scale); 
	SHORT getPageInterval(Scale scale);
	SHORT getPageNumFontHeight(Scale scale);
	SHORT getTactHeight(Scale scale);
	SHORT getEventInterval(Scale scale, BeatType beatType);
	SHORT getHorizontalBorder(Scale scale);
	SHORT getVerticalBorder(Scale scale);
	SHORT getHeadVerticalBorder(Scale scale);
	SHORT getTactBorder(Scale scale);
	SHORT getTactNumFontHeight(Scale scale);
	SHORT getCompositionNameFontHeight(Scale scale);
	SHORT getArtistNameFontHeight(Scale scale);
	SHORT getTrackInfoFontHeight(Scale scale);
	SHORT getInformationIntervalHeight(Scale scale);
	HFONT getFont(UCHAR fontHeight);
	HPEN getPen(int style, int width, COLORREF color);
	HBRUSH getSolidBrush(COLORREF color);
private:
	map<SHORT, HFONT> fonts;
	map<COLORREF, HBRUSH> brushes;
	map<COLORREF, HPEN> pens;
	static SHORT GetByScale(Scale scale, SHORT size);
};

