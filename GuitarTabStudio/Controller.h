#pragma once
#include "Windows.h"

class Controller {
	virtual void processMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
};