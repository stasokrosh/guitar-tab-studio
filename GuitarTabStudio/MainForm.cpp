#include "stdafx.h"
#include "MainForm.h"
#include "Timer.h"

MainForm::MainForm(HINSTANCE hInstance) {
	this->hInstance = hInstance;
	this->hWnd = CreateWindowW(MAIN_FORM_CLASS_NAME, MAIN_FORM_DEFAULT_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, this->hInstance, nullptr);
	SetClassLong(this->hWnd, 0, (long)this);
	this->timer = new Timer(this->hWnd);

}


MainForm::~MainForm() {}

void MainForm::Show() {
	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
}

HWND MainForm::getHWND() {
	return this->hWnd;
}

Timer * MainForm::getTimer() {
	return this->timer;
}

BOOL MainForm::RegisterMainFormClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = sizeof(MainForm*);
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP15), IMAGE_ICON, GetSystemMetrics(SM_CXICON),
		GetSystemMetrics(SM_CYICON), 0);
	wcex.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP15), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON), 0);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GUITARTABSTUDIO);
	wcex.lpszClassName = MAIN_FORM_CLASS_NAME;

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK MainForm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	MainForm* mainForm = (MainForm*)GetClassLong(hWnd, 0);
	switch (message) {
	case WM_TIMER: {
		mainForm->getTimer()->processMessage(message);
	} break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND MainForm::CreateToolBar() {
	
	HIMAGELIST hImageList = ImageList_Create(31, 30, ILC_COLOR16, TOOLBAR_BTN_COUNT, 0);
	int wholeBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1)), NULL);
	int halfBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2)), NULL);
	int quaterBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3)), NULL);
	int eigthBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4)), NULL);
	int sixteenthBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP5)), NULL);
	int thirtyTwoBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP6)), NULL);
	int sixtyFourBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP7)), NULL);
	int dotBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP8)), NULL);
	int pauseBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP11)), NULL);
	
	TBBUTTON tbButtons3[TOOLBAR_BTN_COUNT] =
	{
		{ wholeBtnNum ,  WHOLE_BTN,  TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ halfBtnNum, HALF_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ quaterBtnNum, QUATER_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ eigthBtnNum, EIGHTH_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ sixteenthBtnNum, SIXTEENTH_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ thirtyTwoBtnNum, THIRTY_SECOND_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ sixtyFourBtnNum, SIXTY_FOURTH_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ dotBtnNum, DOT_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ pauseBtnNum, PAUSE_BTN, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 }
	};
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_CHILD | WS_VISIBLE | CCS_VERT | WS_BORDER, 0, 0, 0, 0,
		this->hWnd, NULL, this->hInstance, NULL);
	SendMessage(hWndToolbar, TB_SETIMAGELIST, 0, (LPARAM)hImageList);
	SendMessage(hWndToolbar, TB_LOADIMAGES, (WPARAM)IDB_STD_LARGE_COLOR, (LPARAM)HINST_COMMCTRL);
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, TOOLBAR_BTN_COUNT, (LPARAM)&tbButtons3);

	return hWndToolbar;
}

