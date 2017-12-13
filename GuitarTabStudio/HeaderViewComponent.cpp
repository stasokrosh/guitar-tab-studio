#include "stdafx.h"
#include "HeaderViewComponent.h"


HeaderViewComponent::HeaderViewComponent(ViewInfo* viewInfo, CompositionInfo* compositionInfo, TrackInfo* trackInfo, Instrument* instrument) : ViewComponent(viewInfo, NULL, NULL) {
	this->compositionInfo = compositionInfo;
	this->trackInfo = trackInfo;
	this->instrument = instrument;
	USHORT pageWidth = this->viewInfo->viewConfiguration->getPageWidth(this->viewInfo->scale);
	USHORT verticalBorder = this->viewInfo->viewConfiguration->getVerticalBorder(this->viewInfo->scale);
	USHORT compositionNameHeight = this->viewInfo->viewConfiguration->getCompositionNameFontHeight(this->viewInfo->scale);
	USHORT artistNameHeight = this->viewInfo->viewConfiguration->getArtistNameFontHeight(this->viewInfo->scale);
	USHORT intervalHeight = this->viewInfo->viewConfiguration->getInformationIntervalHeight(this->viewInfo->scale);
	USHORT trackInformationHeight = this->viewInfo->viewConfiguration->getTrackInfoFontHeight(this->viewInfo->scale);
	USHORT height = verticalBorder + compositionNameHeight + artistNameHeight + trackInformationHeight + intervalHeight * 2;
	this->resize(pageWidth, height);
}


HeaderViewComponent::~HeaderViewComponent() {}

void HeaderViewComponent::selfDraw(HDC hdc) {
	USHORT verticalBorder = this->viewInfo->viewConfiguration->getVerticalBorder(this->viewInfo->scale);
	USHORT horizontalBorder = this->viewInfo->viewConfiguration->getHorizontalBorder(this->viewInfo->scale);
	USHORT compositionNameHeight = this->viewInfo->viewConfiguration->getCompositionNameFontHeight(this->viewInfo->scale);
	USHORT artistNameHeight = this->viewInfo->viewConfiguration->getArtistNameFontHeight(this->viewInfo->scale);
	USHORT intervalHeight = this->viewInfo->viewConfiguration->getInformationIntervalHeight(this->viewInfo->scale);
	USHORT trackInformationHeight = this->viewInfo->viewConfiguration->getTrackInfoFontHeight(this->viewInfo->scale);
	RECT rect;
	rect.top = this->getX() + verticalBorder;
	rect.bottom = rect.top + compositionNameHeight;
	rect.left = this->getX() + horizontalBorder;
	rect.right = this->getX() + this->getWidth() - horizontalBorder;
	HFONT font = this->viewInfo->viewConfiguration->getFont(compositionNameHeight);
	DrawText(hdc, this->compositionInfo->name.c_str, this->compositionInfo->name.size(), &rect, DT_CENTER);
	rect.top = rect.bottom + intervalHeight;
	rect.bottom = rect.top + artistNameHeight;
	HFONT font = this->viewInfo->viewConfiguration->getFont(artistNameHeight);
	DrawText(hdc, this->compositionInfo->author.c_str, this->compositionInfo->author.size(), &rect, DT_CENTER);
	rect.top = rect.bottom + intervalHeight;
	rect.bottom = rect.top + trackInformationHeight;
	HFONT font = this->viewInfo->viewConfiguration->getFont(trackInformationHeight);
	wstring trackInfo = L"Track : " + this->trackInfo->name + L"(" + this->instrument->getName() + L")";
	DrawText(hdc, trackInfo.c_str, trackInfo.size(), &rect, DT_LEFT);
	wstring tempoInfo = L"Tempo = " + to_wstring(this->compositionInfo->tempo);
	DrawText(hdc, trackInfo.c_str, trackInfo.size(), &rect, DT_RIGHT);
}
