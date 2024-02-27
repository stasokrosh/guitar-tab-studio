#include "stdafx.h"
#include "NotesForm.h"


NotesForm::NotesForm(HWND parent, HINSTANCE hInstance) {
	this->hWnd = CreateWindowW(NOTES_FORM_CLASS_NAME, NOTES_FORM_DEFAULT_TITLE, WS_OVERLAPPEDWINDOW,
		0, 37, 100, 100, parent, nullptr, hInstance, nullptr);
	SetClassLongPtr(this->hWnd, 0, (LONG_PTR)this);
	ShowWindow(this->hWnd, 1);
	UpdateWindow(this->hWnd);
}

NotesForm::~NotesForm() {}

BOOL NotesForm::RegisterNotesFormClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = sizeof(NotesForm*);
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = NOTES_FORM_CLASS_NAME;

	return RegisterClassExW(&wcex);
}

HWND NotesForm::getHwnd() {
	return HWND();
}

LRESULT NotesForm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	NotesForm* notesForm = (NotesForm*)GetClassLongPtr(hWnd, 0);
	switch (message) {
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	} break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
