#include "stdafx.h"
#include "ViewConfiguration.h"


ViewConfiguration::ViewConfiguration() {}


ViewConfiguration::~ViewConfiguration() {
	this->fonts.clear();
	this->pens.clear();
	this->brushes.clear();
}

SHORT ViewConfiguration::getPageWidth(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_WIDTH);
}

SHORT ViewConfiguration::getPageHeight(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT);
}

SHORT ViewConfiguration::getPageInterval(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 20);
}

SHORT ViewConfiguration::getTactHeight(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 8);
}

SHORT ViewConfiguration::getEventInterval(Scale scale, BeatType beatType) {
	return GetByScale(scale, DEFAULT_PAGE_WIDTH / 40 + 64 / beatType);
}

SHORT ViewConfiguration::getHorizontalBorder(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 15);
}

SHORT ViewConfiguration::getVerticalBorder(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 25);
}

SHORT ViewConfiguration::getHeadVerticalBorder(Scale scale) {
	return this->getVerticalBorder(scale) * 2;
}

SHORT ViewConfiguration::getTactBorder(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_WIDTH / 40);
}

SHORT ViewConfiguration::getTactNumFontHeight(Scale scale) {
	return this->getTactHeight(scale) / 10;
}

SHORT ViewConfiguration::getCompositionNameFontHeight(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 25);
}

SHORT ViewConfiguration::getArtistNameFontHeight(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 30);
}

SHORT ViewConfiguration::getTrackInfoFontHeight(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 50);
}

SHORT ViewConfiguration::getInformationIntervalHeight(Scale scale) {
	return this->getCompositionNameFontHeight(scale) / 2;
}

SHORT ViewConfiguration::getPageNumFontHeight(Scale scale) {
	return GetByScale(scale, DEFAULT_PAGE_HEIGHT / 50);
}

HFONT ViewConfiguration::getFont(UCHAR fontHeight) {
	map<SHORT, HFONT>::iterator iterator = this->fonts.find(fontHeight);
	if (iterator != this->fonts.end()) {
		return (*iterator).second;
	} else {
		HFONT font = CreateFont(fontHeight, 0, 0, 0,
			FW_NORMAL, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_ROMAN,
			L"Times New Roman");
		this->fonts.insert(pair<SHORT, HFONT>(fontHeight, font));
		return font;
	}
}

HPEN ViewConfiguration::getPen(int style, int width, COLORREF color) {
	map<COLORREF, HPEN>::iterator iterator = this->pens.find(color);
	if (iterator != this->pens.end()) {
		return (*iterator).second;
	} else {
		HPEN pen = CreatePen(style, width, color);
		this->pens.insert(pair<COLORREF, HPEN>(color, pen));
		return pen;
	}
}

HBRUSH ViewConfiguration::getSolidBrush(COLORREF color) {
	map<COLORREF, HBRUSH>::iterator iterator = this->brushes.find(color);
	if (iterator != this->brushes.end()) {
		return (*iterator).second;
	} else {
		HBRUSH brush = CreateSolidBrush(color);
		this->brushes.insert(pair<COLORREF, HBRUSH>(color, brush));
		return brush;
	}
}

SHORT ViewConfiguration::GetByScale(Scale scale, SHORT size) {
	return (size * scale) / MDM;
}
