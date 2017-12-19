#pragma once
#include "ViewComponent.h"
#include "GuitarView.h"
#include <string>

using namespace std;

class GuitarNoteViewComponent :
	public ViewComponent {
public:
	GuitarNoteViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, CHAR* note, UCHAR stringCount, BOOL selected);
	~GuitarNoteViewComponent();
protected:
	virtual void selfDraw(HDC hdc);
private:
	CHAR* note;
	BOOL selected;
	UCHAR stringCount;
};

