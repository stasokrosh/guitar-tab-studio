#pragma once
#include "Windows.h"
#include "MainForm.h"

class Application {
public:
	Application(HINSTANCE hInstance, LPWSTR cmdLine);
	~Application();
	BOOL initialize();
	int run();
private:
	HINSTANCE hInstance;
	LPWSTR cmdLine;
	MainForm* mainForm;
};