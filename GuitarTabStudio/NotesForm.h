#pragma once
#include "resource.h"

#define NOTES_FORM_CLASS_NAME L"NotesForm"
#define NOTES_FORM_DEFAULT_TITLE L""

class NotesForm {
public:
	NotesForm(HWND parent, HINSTANCE hInstance);
	~NotesForm();
	static BOOL RegisterNotesFormClass(HINSTANCE hInstance);
	HWND getHwnd();
private:
	HWND hWnd;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

