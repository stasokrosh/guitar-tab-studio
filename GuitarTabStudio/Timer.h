#pragma once
#include "Callback.h"
#include <map>
#include <vector>

using namespace std;

class Timer {
public:
	Timer(HWND hwnd);
	~Timer();
	void processMessage(UINT timerId);
	void addCallBack(Callback* callback, UINT elapse);
	BOOL deleteCallBack(Callback* callback);
private:
	HWND hwnd;
	map<UINT, UINT> timerByElapse;
	map<UINT, UINT> elapseByTimer;
	map<UINT, vector<Callback*>> listenersByTimer;
	map<Callback*, UINT> elapseByListener;
};

