#pragma once
#include "ViewComponent.h"
#include "NotesEditor.h" 
#include "EventContainerViewComponent.h"
#include "EventViewComponent.h"
#include <string>

using namespace std;

template<class T>
class TactViewComponent : public ViewComponent{
public:
	TactViewComponent(ViewInfo* viewInfo, Callback* doubleClickCallback, USHORT num);
	~TactViewComponent();
	virtual void addEvents(vector<T*> events);
	virtual void resize(USHORT width, USHORT height);
protected:
	EventContainerViewComponent<T>* eventContainer;
	USHORT num;

	virtual void selfDraw(HDC hdc);
};

