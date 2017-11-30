#include "stdafx.h"
#include "Timer.h"


Timer::Timer(HWND hwnd) {
	this->hwnd = hwnd;
}


Timer::~Timer() {}

void Timer::processMessage(UINT timerId) {
	map<UINT, vector<Callback*>>::iterator listenersIterator = this->listenersByTimer.find(timerId);
	if (listenersIterator != this->listenersByTimer.end()) {
		for (Callback* callback : this->listenersByTimer[timerId]) {
			callback->call();
		}
	}
}

void Timer::addCallBack(Callback* pCallback, UINT elapse) {
	UINT oldElapse = this->elapseByListener.find(pCallback) == this->elapseByListener.end() ?
		0 : this->elapseByListener[pCallback];
	if (oldElapse != elapse) {
		UINT oldTimerId = this->timerByElapse[elapse];
		vector<Callback*>::iterator vectorIterator = this->listenersByTimer[oldTimerId].begin();
		while (*vectorIterator != pCallback) {
			vectorIterator++;
		}
		this->listenersByTimer[oldTimerId].erase(vectorIterator, vectorIterator);
		
		this->elapseByListener[pCallback] = elapse;
		UINT timerId;
		map<UINT, UINT>::iterator timerIdIterator = this->timerByElapse.find(elapse);
		if (timerIdIterator == this->timerByElapse.end()) {
			timerId = 0;
			while (this->listenersByTimer.find(timerId) == this->listenersByTimer.end()) {
				timerId++;
			}
			this->timerByElapse[elapse] = timerId;
			this->elapseByTimer[timerId] = elapse;
			vector<Callback*> callbackVector = { pCallback };
			this->listenersByTimer[timerId] = callbackVector;
			SetTimer(hwnd, timerId, elapse, NULL);
		} else {
			timerId = this->timerByElapse[elapse];
		}
		this->listenersByTimer[timerId].push_back(pCallback);
	}
			
}

BOOL Timer::deleteCallBack(Callback * pCallback) {
	if (this->elapseByListener.find(pCallback) == this->elapseByListener.end()) {
		return FALSE;
	}
	UINT elapse = this->elapseByListener[pCallback];
	UINT timerId = this->timerByElapse[elapse];
	vector<Callback*>::iterator vectorIterator = this->listenersByTimer[timerId].begin();
	while (*vectorIterator != pCallback) {
		vectorIterator++;
	}
	this->listenersByTimer[timerId].erase(vectorIterator, vectorIterator);
	if (this->listenersByTimer[timerId].size() == 0) {
		map<UINT, vector<Callback*>>::iterator vectorIterator = this->listenersByTimer.find(timerId);
		this->listenersByTimer.erase(vectorIterator, vectorIterator);
		map<UINT, UINT>::iterator iterator = this->timerByElapse.find(elapse);
		this->timerByElapse.erase(iterator, iterator);
		iterator = this->elapseByTimer.find(timerId);
		this->elapseByTimer.erase(iterator, iterator);
		KillTimer(hwnd, timerId);
	}
	map<Callback*, UINT>::iterator callbackIterator = this->elapseByListener.find(pCallback);
	this->elapseByListener.erase(callbackIterator, callbackIterator);
	return TRUE;
}
