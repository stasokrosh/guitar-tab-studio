#pragma once
#include "Windows.h"
#include "View.h"
#include <vector>
#include "Callback.h"

using namespace std;

class ViewComponent {
public:
	ViewComponent(ViewInfo* viewInfo, Callback* clickCallback, Callback* doubleClickCallback);
	~ViewComponent();
	void draw(HDC hdc);
	BOOL containsDot(USHORT x, USHORT y);
	virtual void click(USHORT x, USHORT y);
	virtual void doubleClick(USHORT x, USHORT y);
	virtual void move(USHORT x, USHORT y);
	virtual void resize(USHORT width, USHORT height);
	vector<ViewComponent*>* getComponents();
	USHORT getX();
	USHORT getY();
	USHORT getWidth();
	USHORT getHeight();
	ViewInfo* getViewInfo();
protected:
	vector<ViewComponent*> components;
	ViewInfo* viewInfo;

	virtual void updateSize();
	virtual void selfDraw(HDC hdc);
private:
	Callback* clickCallBack;
	Callback* doubleClickCallback;
	USHORT x;
	USHORT y;
	USHORT width;
	USHORT height;
};

