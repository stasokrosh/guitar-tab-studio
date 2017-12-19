#include "stdafx.h"
#include "HeaderViewComponent.h"


HeaderViewComponent::HeaderViewComponent(ViewInfo* viewInfo, CompositionInfo* compositionInfo, TrackInfo* trackInfo, Instrument* instrument) : ViewComponent(viewInfo, NULL, NULL) {
	this->compositionInfo = compositionInfo;
	this->trackInfo = trackInfo;
	this->instrument = instrument;
	SHORT pageWidth = this->viewInfo->viewConfiguration->getPageWidth(this->viewInfo->scale);
	SHORT verticalHeadBorder = this->viewInfo->viewConfiguration->getHeadVerticalBorder(this->viewInfo->scale);
	SHORT compositionNameHeight = this->viewInfo->viewConfiguration->getCompositionNameFontHeight(this->viewInfo->scale);
	SHORT artistNameHeight = this->viewInfo->viewConfiguration->getArtistNameFontHeight(this->viewInfo->scale);
	SHORT intervalHeight = this->viewInfo->viewConfiguration->getInformationIntervalHeight(this->viewInfo->scale);
	SHORT trackInformationHeight = this->viewInfo->viewConfiguration->getTrackInfoFontHeight(this->viewInfo->scale);
	SHORT height = verticalHeadBorder + compositionNameHeight + artistNameHeight + trackInformationHeight + intervalHeight * 2;
	this->resize(pageWidth, height);
}


HeaderViewComponent::~HeaderViewComponent() {}

void HeaderViewComponent::selfDraw(HDC hdc) {
	SHORT verticalHeadBorder = this->viewInfo->viewConfiguration->getHeadVerticalBorder(this->viewInfo->scale);
	SHORT horizontalBorder = this->viewInfo->viewConfiguration->getHorizontalBorder(this->viewInfo->scale);
	SHORT compositionNameHeight = this->viewInfo->viewConfiguration->getCompositionNameFontHeight(this->viewInfo->scale);
	SHORT artistNameHeight = this->viewInfo->viewConfiguration->getArtistNameFontHeight(this->viewInfo->scale);
	SHORT intervalHeight = this->viewInfo->viewConfiguration->getInformationIntervalHeight(this->viewInfo->scale);
	SHORT trackInformationHeight = this->viewInfo->viewConfiguration->getTrackInfoFontHeight(this->viewInfo->scale);
	RECT rect;
	rect.top = this->getY() + verticalHeadBorder;
	rect.bottom = rect.top + compositionNameHeight;
	rect.left = this->getX() + horizontalBorder;
	rect.right = this->getX() + this->getWidth() - horizontalBorder;
	HFONT font = this->viewInfo->viewConfiguration->getFont(compositionNameHeight);
	HANDLE oldFont = SelectObject(hdc, font);
	DrawText(hdc, this->compositionInfo->name.c_str(), this->compositionInfo->name.size(), &rect, DT_CENTER);
	rect.top = rect.bottom + intervalHeight;
	rect.bottom = rect.top + artistNameHeight;
	font = this->viewInfo->viewConfiguration->getFont(artistNameHeight);
	SelectObject(hdc, font);
	DrawText(hdc, this->compositionInfo->author.c_str(), this->compositionInfo->author.size(), &rect, DT_CENTER);
	rect.top = rect.bottom + intervalHeight;
	rect.bottom = rect.top + trackInformationHeight;
	font = this->viewInfo->viewConfiguration->getFont(trackInformationHeight);
	SelectObject(hdc, font);
	wstring trackInfo = L"Track : " + this->trackInfo->name + L"(" + this->instrument->getName() + L")";
	DrawText(hdc, trackInfo.c_str(), trackInfo.size(), &rect, DT_LEFT);
	wstring tempoInfo = L"Tempo = " + to_wstring(this->compositionInfo->tempo);
	DrawText(hdc, tempoInfo.c_str(), tempoInfo.size(), &rect, DT_RIGHT);
	SelectObject(hdc, oldFont);
}
