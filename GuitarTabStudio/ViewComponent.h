#pragma once
#include "Windows.h"
#include <vector>

using namespace std;

class ViewComponent {
public:
	ViewComponent(USHORT x, USHORT y, USHORT width, USHORT height);
	~ViewComponent();
	void draw(HDC hdc, USHORT width, USHORT height);
	BOOL containsDot(USHORT x, USHORT y);
	virtual void click(USHORT x, USHORT y);
	virtual void doubleClick(USHORT x, USHORT y);
	virtual void move(USHORT x, USHORT y);
	virtual void resize(USHORT width, USHORT height);
	vector<ViewComponent*> components;
protected:
	virtual void selfDraw(HDC hdc, USHORT width, USHORT height) = 0;
	virtual void selfClick() = 0;
	virtual void selfDoubleClick() = 0;
private:
	USHORT x;
	USHORT y;
	USHORT width;
	USHORT height;
};

