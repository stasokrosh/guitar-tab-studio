#pragma once
#include "resource.h"
#include "Windows.h"
#include "Commctrl.h"
#include "Timer.h"

#define MAIN_FORM_CLASS_NAME L"MainForm"
#define MAIN_FORM_DEFAULT_TITLE L"GuitarTabStudio"

#define TOOLBAR_BTN_COUNT 9

#define WHOLE_BTN 1
#define HALF_BTN 2
#define DOT_BTN 3
#define QUATER_BTN 4
#define PAUSE_BTN 5
#define EIGHTH_BTN 8
#define SIXTEENTH_BTN 16
#define THIRTY_SECOND_BTN 32
#define SIXTY_FOURTH_BTN 64

class MainForm {
public:
	MainForm(HINSTANCE hInstance);
	~MainForm();
	void Show();
	HWND getHWND();
	Timer* getTimer();
	static BOOL RegisterMainFormClass(HINSTANCE hInstance);
private:
	HWND hWnd;
	HINSTANCE hInstance;
	Timer* timer;
	
	HWND CreateToolBar();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

