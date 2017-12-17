#include "stdafx.h"
#include "ViewConfiguration.h"


ViewConfiguration::ViewConfiguration() {}


ViewConfiguration::~ViewConfiguration() {}

USHORT ViewConfiguration::getPageWidth(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getPageHeight(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getPageInterval(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getTactHeight(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getEventInterval(Scale scale, BeatType beatType) {
	return USHORT();
}

USHORT ViewConfiguration::getHorizontalBorder(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getVerticalBorder(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getTactBorder(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getTactNumFontHeight(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getCompositionNameFontHeight(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getArtistNameFontHeight(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getTrackInfoFontHeight(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getInformationIntervalHeight(Scale scale) {
	return USHORT();
}

USHORT ViewConfiguration::getPageNumFontHeight(Scale scale) {
	return USHORT();
}

HFONT ViewConfiguration::getFont(UCHAR fontHeight) {
	return HFONT();
}

HPEN ViewConfiguration::getPen(int style, int width, COLORREF color) {
	return HPEN();
}

HBRUSH ViewConfiguration::getSolidBrush(COLORREF color) {
	return HBRUSH();
}
