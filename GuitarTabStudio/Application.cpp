#include "stdafx.h"
#include "Application.h"


Application::Application(HINSTANCE hInstance, LPWSTR cmdLine) {
	this->hInstance = hInstance;
	this->cmdLine = cmdLine;
}

Application::~Application() {
	delete this->mainForm;
}

BOOL Application::initialize() {
	MainForm::RegisterMainFormClass(this->hInstance);
	this->mainForm = new MainForm(this->hInstance);
	return TRUE;
}

int Application::run() {
	this->mainForm->Show();
	
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
	return 0;
}
