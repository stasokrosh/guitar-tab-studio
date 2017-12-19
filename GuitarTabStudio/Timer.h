#pragma once
#include "Callback.h"
#include <map>
#include <vector>

#define TIMER_ID 1

using namespace std;

class Timer {
public:
	Timer(HWND hwnd);
	~Timer();
	void processMessage(SHORT timerId);
	void addCallBack(Callback* callback, UINT elapse);
	void deleteCallBack();
private:
	HWND hwnd;
	UINT elapse;
	Callback* callback;
};

