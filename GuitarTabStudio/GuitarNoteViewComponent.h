#pragma once
#include "ViewComponent.h"
#include "GuitarView.h"
#include <string>

using namespace std;

class GuitarNoteViewComponent :
	public ViewComponent {
public:
	GuitarNoteViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, CHAR* note, UCHAR stringCount, BOOL* selected);
	~GuitarNoteViewComponent();
	virtual void updateSize();
protected:
	virtual void selfDraw(HDC hdc, HPEN mainPen);
private:
	CHAR* note;
	BOOL* selected;
	UCHAR stringCount;
};

