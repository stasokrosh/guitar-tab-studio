#pragma once
#include "Windows.h"
#include "ViewInfo.h"
#include "Callback.h"
#include <vector>

using namespace std;

class ViewComponent {
public:
	ViewComponent(ViewInfo* viewInfo, Callback* clickCallback, Callback* doubleClickCallback);
	virtual ~ViewComponent();
	void draw(HDC hdc, SHORT width, SHORT height);
	BOOL containsDot(SHORT x, SHORT y);
	virtual void click(SHORT x, SHORT y);
	virtual void doubleClick(SHORT x, SHORT y);
	virtual void move(SHORT x, SHORT y);
	virtual void resize(SHORT width, SHORT height);
	vector<ViewComponent*>* getComponents();
	SHORT getX();
	SHORT getY();
	SHORT getWidth();
	SHORT getHeight();
	ViewInfo* getViewInfo();
protected:
	vector<ViewComponent*> components;
	ViewInfo* viewInfo;
	SHORT x;
	SHORT y;
	SHORT width;
	SHORT height;

	virtual void updateSize();
	virtual void selfDraw(HDC hdc);
private:
	Callback* clickCallBack;
	Callback* doubleClickCallback;

	BOOL isVisible(SHORT width, SHORT height);
};

