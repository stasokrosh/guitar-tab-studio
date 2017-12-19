#include "stdafx.h"
#include "Timer.h"


Timer::Timer(HWND hwnd) {
	this->hwnd = hwnd;
	this->callback = NULL;
}


Timer::~Timer() {}

void Timer::processMessage(SHORT timerId) {
	if (timerId = TIMER_ID && this->callback != NULL) {
		if (this->callback != NULL) {
			this->callback->call();
		}
	}
}

void Timer::addCallBack(Callback* pCallback, UINT elapse) {
	this->callback = pCallback;
	SetTimer(this->hwnd, TIMER_ID, elapse, NULL);
}

void Timer::deleteCallBack() {
	KillTimer(this->hwnd, TIMER_ID);
}
