#include "stdafx.h"
#include "MainForm.h"
#include "Timer.h"

MainForm::MainForm(HINSTANCE hInstance) {
	this->hInstance = hInstance;
	this->hWnd = CreateWindowW(MAIN_FORM_CLASS_NAME, MAIN_FORM_DEFAULT_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, this->hInstance, nullptr);
	SetClassLong(this->hWnd, 0, (long)this);
	this->toolBar = this->CreateToolBar();
	this->notesEditor = NULL;
	this->player = NULL;
	this->trackViewComponent = NULL;
	this->timer = new Timer(this->hWnd);
	this->viewInfo.mainColor = RGB(0, 0, 0);
	this->viewInfo.mainBackgroundColor = RGB(0xFF, 0xFF, 0xFF);
	this->viewInfo.selectionColor = RGB(0, 0, 0xFF);
	this->viewInfo.errorColor = RGB(0xFF, 0, 0);
	this->viewInfo.scale = MDM;
	this->viewInfo.viewConfiguration = new ViewConfiguration();
}

MainForm::~MainForm() {}

void MainForm::Show() {
	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);
	this->update();
}

HWND MainForm::getHWND() {
	return this->hWnd;
}

Timer * MainForm::getTimer() {
	return this->timer;
}

void MainForm::update() {
	this->updateToolbarBtn();
	this->updateMenuBtn();
	this->updateWindowTitle();
	this->getViewComponent();
	this->redraw();
}

void MainForm::setNotesEditor(NotesEditor * notesEditor) {
	this->notesEditor = notesEditor;
}

void MainForm::setPlayer(Player * player) {
	this->player = player;
}

Callback * MainForm::getUpdateFormCallback() {
	return new UpdateFormCallback(this);
}

BOOL MainForm::RegisterMainFormClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = sizeof(MainForm*);
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = 0;
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = MAIN_FORM_CLASS_NAME;

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK MainForm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	MainForm* mainForm = (MainForm*)GetClassLong(hWnd, 0);
	switch (message) {
	case WM_TIMER: {
		mainForm->getTimer()->processMessage(wParam);
	} break;
	case WM_DESTROY: {
		PostQuitMessage(0);
	} break;
	case WM_COMMAND: {
		if (lParam == 0) {
			mainForm->processMenuButtonClick(wParam);
		} else {
			WORD code = HIWORD(wParam);
			if (code == BN_CLICKED) {
				mainForm->processToolBarButtonClick(LOWORD(wParam));
			}
		}
	} break;
	case WM_KEYUP: {
		mainForm->processKeyUp(wParam);
	} break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(mainForm->getHWND(), &ps);
		mainForm->draw(hdc);
		EndPaint(mainForm->getHWND(), &ps);
	} break;
	case WM_LBUTTONUP: {
		if (wParam == MK_CONTROL) {
			mainForm->processControlClick(LOWORD(lParam), HIWORD(lParam));
		} else {
			mainForm->processClick(LOWORD(lParam), HIWORD(lParam));
		}
	} break;
	case WM_MOUSEWHEEL: {
		mainForm->processWheel(lParam, wParam);
	} break;
	case WM_SIZE: {
		mainForm->processSizing();
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	} 
	return 0;
}

HWND MainForm::CreateToolBar() {

	HIMAGELIST hImageList = ImageList_Create(32, 32, ILC_COLOR16, TOOLBAR_BTN_COUNT, 0);
	int wholeBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1)), NULL);
	int halfBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2)), NULL);
	int quaterBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3)), NULL);
	int eigthBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4)), NULL);
	int sixteenthBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP5)), NULL);
	int thirtyTwoBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP6)), NULL);
	int sixtyFourBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP7)), NULL);
	int tripleBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP13)), NULL);
	int dotBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP8)), NULL);
	int pauseBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP11)), NULL);
	int repriseBeginNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP12)), NULL);
	int repriseEndNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP10)), NULL);
	int chordUpBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP14)), NULL);
	int chordDownBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP9)), NULL);
	int guitarPropertiesNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP15)), NULL);
	int playBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP19)), NULL);
	int pausePlayBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP18)), NULL);
	int stopBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP21)), NULL);
	int nextTrackBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP17)), NULL);
	int prevTrackBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP16)), NULL);
	int addTrackBtnNum = ImageList_Add(hImageList, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP20)), NULL);
	TBBUTTON tbButtons[TOOLBAR_BTN_COUNT] =
	{
		{ wholeBtnNum,  WHOLE_BTN,  TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ halfBtnNum, HALF_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ quaterBtnNum, QUATER_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ eigthBtnNum, EIGHTH_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ sixteenthBtnNum, SIXTEENTH_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ thirtyTwoBtnNum, THIRTY_SECOND_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ sixtyFourBtnNum, SIXTY_FOURTH_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ tripleBtnNum, TRIPLE_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ dotBtnNum, DOT_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ pauseBtnNum, PAUSE_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ 10, 0, TBSTATE_ENABLED,  BTNS_SEP,{ 0 }, 0L, 0 },
		{ repriseBeginNum, REPRISE_START_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ repriseEndNum, REPRISE_END_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ 10, 0, TBSTATE_ENABLED,  BTNS_SEP,{ 0 }, 0L, 0 },
		{ chordUpBtnNum, CHORD_UP_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ chordDownBtnNum, CHORD_DOWN_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ guitarPropertiesNum, GUITAR_PROPERTIES_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ 20, 0, TBSTATE_ENABLED,  BTNS_SEP,{ 0 }, 0L, 0 },
		{ prevTrackBtnNum, PREV_TRACK_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ playBtnNum, PLAY_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ pausePlayBtnNum, PAUSE_PLAY_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ stopBtnNum, STOP_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ nextTrackBtnNum, NEXT_TRACK_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 },
		{ addTrackBtnNum, ADD_TRACK_BTN, TBSTATE_ENABLED, BTNS_BUTTON,{ 0 }, 0L, 0 }
	};
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | CCS_TOP | WS_BORDER, 0, 0, 0, 0,
		this->hWnd, NULL, this->hInstance, NULL);
	SendMessage(hWndToolbar, TB_SETIMAGELIST, 0, (LPARAM)hImageList);
	SendMessage(hWndToolbar, TB_LOADIMAGES, (WPARAM)IDB_STD_LARGE_COLOR, (LPARAM)HINST_COMMCTRL);
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, TOOLBAR_BTN_COUNT, (LPARAM)&tbButtons);
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	DWORD size = SendMessage(hWndToolbar, TB_GETBUTTONSIZE, 0, 0);
	this->toolBarHeight = LOWORD(size);
	return hWndToolbar;
}

void MainForm::processMenuButtonClick(WORD button) {
	switch (button) {
	case MAKEINTRESOURCE(ID_PLAY_PLAY): {
		if (this->player->getPlaying()) {
			this->player->resume();
		} else {
			this->player->play();
		}
	} break;
	case MAKEINTRESOURCE(ID_PLAY_STOP): {
		this->player->stop();
	} break;
	case MAKEINTRESOURCE(ID_PLAY_PAUSE): {
		this->player->pause();
	} break;
	case MAKEINTRESOURCE(ID_FILE_NEW): {
		CreateCompositionDlg(this->hInstance, this->notesEditor, this->hWnd);
	} break;
	case MAKEINTRESOURCE(ID_FILE_LOAD): {
		this->loadFile();
	} break;
	case MAKEINTRESOURCE(ID_FILE_SAVE): {
		this->saveFile();
	} break;
	case MAKEINTRESOURCE(ID_FILE_SAVEAS): {
		this->saveFileAs();
	} break;
	case MAKEINTRESOURCE(ID_FILE_EXIT): {
		SendMessage(this->hWnd, WM_DESTROY, 0, 0);
	} break;
	case MAKEINTRESOURCE(ID_TRACK_ADDTRACK): {
		CreateTrackDlg(this->hInstance, this->notesEditor, NULL, this->hWnd);
	} break;
	case MAKEINTRESOURCE(ID_TRACK_EDITTRACK): {
		EditTrackDlg(this->hInstance, this->notesEditor,this->hWnd);
	} break;
	case MAKEINTRESOURCE(ID_TRACK_DELETETRACK): {
		this->notesEditor->deleteTrack(this->notesEditor->getSelectedTrack());
	} break;
	case MAKEINTRESOURCE(ID_TRACK_SHOWTRACKS): {
		ShowTracksDlg(this->hInstance, this->notesEditor, this->hWnd);
	} break;
	case  MAKEINTRESOURCE(ID_COMPOSITION_EDITCOMPOSITION): {
		EditCompositionDlg(this->hInstance, this->notesEditor, this->hWnd);
	}
	}
}

void MainForm::processKeyUp(WORD key) {
	if (this->notesEditor->getComposition() != NULL) {
		BOOL guitar = this->notesEditor->getSelectedTrack()->getInstrument()->getInstrumentType() == GUITAR;
		switch (key) {
		case VK_UP: {
			GuitarTrackEditor* guitarTrackEditor =
				reinterpret_cast<GuitarTrackEditor*>(this->notesEditor->getSelectedTrackEditor());
			guitarTrackEditor->moveUp();
		} break;
		case VK_DOWN: {
			if (guitar) {
				GuitarTrackEditor* guitarTrackEditor =
					reinterpret_cast<GuitarTrackEditor*>(this->notesEditor->getSelectedTrackEditor());
				guitarTrackEditor->moveDown();
			}
		} break;
		case VK_LEFT: {
			this->notesEditor->moveBackward();
		} break;
		case VK_RIGHT: {
			this->notesEditor->moveForward();
		} break;
		case VK_BACK: {
			if (guitar) {
				GuitarTrackEditor* guitarTrackEditor =
					reinterpret_cast<GuitarTrackEditor*>(this->notesEditor->getSelectedTrackEditor());
				guitarTrackEditor->deleteSymbol();
			}
		}
		default: {
			if (guitar && key <= 0x39 && key >= 0x30) {
				GuitarTrackEditor* guitarTrackEditor =
					reinterpret_cast<GuitarTrackEditor*>(this->notesEditor->getSelectedTrackEditor());
				guitarTrackEditor->addSymbol(key - 0x30);
			}
		} break;
		}
	}
}

void MainForm::processClick(WORD x, WORD y) {
	if (y > this->toolBarHeight && this->trackViewComponent != NULL) {
		if (this->trackViewComponent->containsDot(x, y)) {
			this->trackViewComponent->click(x, y);
		}
	}
}

void MainForm:: processControlClick(WORD x, WORD y) {
	if (y > this->toolBarHeight && this->trackViewComponent != NULL) {
		if (this->trackViewComponent->containsDot(x, y)) {
			this->trackViewComponent->doubleClick(x, y);
		}
	}
}

void MainForm::processWheel(DWORD lParam, DWORD wParam) {
	SHORT distance = GET_WHEEL_DELTA_WPARAM(wParam);
	BOOL shift = GET_KEYSTATE_WPARAM(wParam) == MK_SHIFT;
	if (shift) {
		Scale* value = &(this->viewInfo.scale);
		if (distance > 0) {
			if (*value == MIN) {
				*value = MDM;
				this->getViewComponent();
			} else {
				if (*value = MDM) {
					*value = HGH;
					this->getViewComponent();
				}
			}
		} else {
			if (*value == HGH) {
				*value = MDM;
				this->getViewComponent();
			} else {
				if (*value = MDM) {
					*value = MIN;
					this->getViewComponent();
				}
			}
		}
		this->redraw();
	} else {
		SHORT startY = this->trackViewComponent->getY();
		this->trackViewComponent->move(this->trackViewComponent->getX(), this->trackViewComponent->getY() + distance);
		if (distance > 0) {
			if (this->trackViewComponent->getY() > 0) {
				this->trackViewComponent->move(this->trackViewComponent->getX(), 0);
			}
		
		} else {
			RECT rect;
			GetClientRect(this->hWnd, &rect);
			if (this->trackViewComponent->getY() + this->trackViewComponent->getHeight() < rect.bottom - rect.top) {
				this->trackViewComponent->move(this->trackViewComponent->getX(), rect.bottom - rect.top - 
					this->trackViewComponent->getHeight());
			}
		}
		if (startY - this->trackViewComponent->getY()) {
			this->redraw();
		}
	}
}

void MainForm::processSizing() {
	SendMessage(this->toolBar, TB_AUTOSIZE, 0, 0);
}

void MainForm::draw(HDC hdc) {
	HDC memDC = CreateCompatibleDC(hdc);
	RECT rect;
	GetClientRect(this->hWnd, &rect);
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	HBITMAP oldbitmap = (HBITMAP)SelectObject(memDC, hbitmap);
	FillRect(memDC, &rect, this->viewInfo.viewConfiguration->getSolidBrush(RGB(0xB0, 0xB0, 0xB0)));
	COLORREF oldTextColor = SetTextColor(hdc, this->viewInfo.mainColor);
	if (this->trackViewComponent != NULL) {
		WORD width = rect.right - rect.left;
		WORD height = rect.bottom - rect.top;
		TrackViewComponent* trackViewComponent = this->trackViewComponent;
		if (width > trackViewComponent->getWidth()) {
			trackViewComponent->move((width - trackViewComponent->getWidth()) 
				/ 2, trackViewComponent->getY());
		}
		trackViewComponent->draw(memDC, width, height);
	}	
	SetTextColor(hdc, oldTextColor);
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldbitmap);
	DeleteObject(hbitmap);
	DeleteDC(memDC);
}

void MainForm::processChangeEventButtons(WORD button) {
	Event* event = this->notesEditor->getSelectedEvent();
	switch (button) {
	case DOT_BTN: {
		UCHAR dotCount = event->getDotCount();
		if (dotCount) {
			notesEditor->setDotCount(0);
		} else {
			notesEditor->setDotCount(1);
		}
	} break;
	case PAUSE_BTN: {
		BOOL pause = event->isPause();
		this->notesEditor->setEventPause(!pause);
	} break;
	case TRIPLE_BTN: {
		BeatTypeEx beatTypeEx = event->getBeatTypeEx();
		if (beatTypeEx == NORMAL) {
			this->notesEditor->setBeatTypeEx(TRIPLE);
		} else {
			this->notesEditor->setBeatTypeEx(NORMAL);
		}
	}
	}
}

void MainForm::processChangeTactButton(WORD button) {
	TactInfo* tactInfo = this->notesEditor->getSelectedTact();
	if (button == REPRISE_START_BTN) {
		this->notesEditor->setRepriseBegin(!(tactInfo->repriseBegin), tactInfo);
	} else {
		UCHAR repriseEnd = tactInfo->repriseEnd;
		repriseEnd = repriseEnd == 2 ? 1 : 2;
		this->notesEditor->setRepriseEnd(repriseEnd, tactInfo);
	}
}

void MainForm::processChangeTrackButton(WORD button) {
	Track* selectedTrack = this->notesEditor->getSelectedTrack();
	vector<Track*> tracks = this->notesEditor->getTracks();
	vector<Track*>::iterator iterator = tracks.begin();
	while (*iterator != selectedTrack) {
		iterator++;
	}
	if (button == NEXT_TRACK_BTN) {
		if (*iterator != tracks.back()) {
			iterator++;
			this->notesEditor->selectTrack(*iterator);
		}
	} else {
		if (*iterator != tracks.front()) {
			iterator--;
			this->notesEditor->selectTrack(*iterator);
		}
	}
}

void MainForm::processGuitarButton(WORD button) {
	GuitarTrackEditor* guitarTrackEditor = reinterpret_cast<GuitarTrackEditor*>(this->notesEditor->getSelectedTrackEditor());
	GuitarEvent* guitarEvent = guitarTrackEditor->getSelectedGuitarEvent();
	switch (button) {
	case CHORD_UP_BTN: {
		if (guitarEvent->getChordDirection() == UP) {
			guitarTrackEditor->setChordDirection(NONE);
		} else {
			guitarTrackEditor->setChordDirection(UP);
		}
	} break;
	case CHORD_DOWN_BTN: {
		if (guitarEvent->getChordDirection() == DOWN) {
			guitarTrackEditor->setChordDirection(NONE);
		} else {
			guitarTrackEditor->setChordDirection(DOWN);
		}
	} break;
	case GUITAR_PROPERTIES_BTN: {
		EditTrackDlg(this->hInstance, this->notesEditor, this->hWnd);
	}break;
	}
}

void MainForm::processChangePlayingButton(WORD button) {
	switch (button) {
	case PLAY_BTN: {
		if (this->player->getPlaying()) {
			this->player->resume();
		} else {
			this->player->play();
		}
	} break;
	case PAUSE_PLAY_BTN: {
		this->player->pause();
	} break;
	case STOP_BTN: {
		this->player->stop();
	} break;
	}
}

void MainForm::updateToolbarBtn() {
	if (this->notesEditor == NULL || this->notesEditor->getComposition() == NULL) {
		this->changeToolBarBtnEnabled(WHOLE_BTN, FALSE);
		this->changeToolBarBtnEnabled(HALF_BTN, FALSE);
		this->changeToolBarBtnEnabled(QUATER_BTN, FALSE);
		this->changeToolBarBtnEnabled(EIGHTH_BTN, FALSE);
		this->changeToolBarBtnEnabled(SIXTEENTH_BTN, FALSE);
		this->changeToolBarBtnEnabled(THIRTY_SECOND_BTN, FALSE);
		this->changeToolBarBtnEnabled(SIXTY_FOURTH_BTN, FALSE);
		this->changeToolBarBtnEnabled(WHOLE_BTN, FALSE);
		this->changeToolBarBtnEnabled(PAUSE_BTN, FALSE);
		this->changeToolBarBtnEnabled(DOT_BTN, FALSE);
		this->changeToolBarBtnEnabled(TRIPLE_BTN, FALSE);
		this->changeToolBarBtnEnabled(REPRISE_START_BTN, FALSE);
		this->changeToolBarBtnEnabled(REPRISE_END_BTN, FALSE);
		this->changeToolBarBtnEnabled(CHORD_UP_BTN, FALSE);
		this->changeToolBarBtnEnabled(CHORD_DOWN_BTN, FALSE);
		this->changeToolBarBtnEnabled(GUITAR_PROPERTIES_BTN, FALSE);
		this->changeToolBarBtnEnabled(PREV_TRACK_BTN, FALSE);
		this->changeToolBarBtnEnabled(PLAY_BTN, FALSE);
		this->changeToolBarBtnEnabled(PAUSE_PLAY_BTN, FALSE);
		this->changeToolBarBtnEnabled(STOP_BTN, FALSE);
		this->changeToolBarBtnEnabled(NEXT_TRACK_BTN, FALSE);
		this->changeToolBarBtnEnabled(ADD_TRACK_BTN, FALSE);
	} else {
		if (this->player->getPlaying()) {
			this->changeToolBarBtnEnabled(WHOLE_BTN, FALSE);
			this->changeToolBarBtnEnabled(HALF_BTN, FALSE);
			this->changeToolBarBtnEnabled(QUATER_BTN, FALSE);
			this->changeToolBarBtnEnabled(EIGHTH_BTN, FALSE);
			this->changeToolBarBtnEnabled(SIXTEENTH_BTN, FALSE);
			this->changeToolBarBtnEnabled(THIRTY_SECOND_BTN, FALSE);
			this->changeToolBarBtnEnabled(SIXTY_FOURTH_BTN, FALSE);
			this->changeToolBarBtnEnabled(WHOLE_BTN, FALSE);
			this->changeToolBarBtnEnabled(PAUSE_BTN, FALSE);
			this->changeToolBarBtnEnabled(DOT_BTN, FALSE);
			this->changeToolBarBtnEnabled(TRIPLE_BTN, FALSE);
			this->changeToolBarBtnEnabled(REPRISE_START_BTN, FALSE);
			this->changeToolBarBtnEnabled(REPRISE_END_BTN, FALSE);
			this->changeToolBarBtnEnabled(CHORD_UP_BTN, FALSE);
			this->changeToolBarBtnEnabled(CHORD_DOWN_BTN, FALSE);
			this->changeToolBarBtnEnabled(GUITAR_PROPERTIES_BTN, FALSE);
			this->changeToolBarBtnEnabled(PREV_TRACK_BTN, FALSE);
			this->changeToolBarBtnEnabled(NEXT_TRACK_BTN, FALSE);
			this->changeToolBarBtnEnabled(ADD_TRACK_BTN, FALSE);
			if (this->player->getStopped()) {
				this->changeToolBarBtnEnabled(PLAY_BTN, TRUE);
				this->changeToolBarBtnEnabled(PAUSE_PLAY_BTN, FALSE);
				this->changeToolBarBtnEnabled(STOP_BTN, TRUE);
			} else {
				this->changeToolBarBtnEnabled(PLAY_BTN, FALSE);
				this->changeToolBarBtnEnabled(PAUSE_PLAY_BTN, TRUE);
				this->changeToolBarBtnEnabled(STOP_BTN, TRUE);
			}
		} else {
			this->updateChangeEventBtn();
			this->updateChangeTactBtn();
			this->updateGuitarBtn();
			this->updateChangeTrackBtn();
			this->updatePlayBtn();
			this->changeToolBarBtnEnabled(ADD_TRACK_BTN, TRUE);
		}
	}
}
void MainForm::updateChangeEventBtn() {
	this->updateSetBeatTypeBtn();
	Event* event = this->notesEditor->getSelectedEvent();
	this->changeToolBarBtnEnabled(PAUSE_BTN, TRUE);
	this->changeToolBarBtnEnabled(DOT_BTN, TRUE);
	this->changeToolBarBtnEnabled(TRIPLE_BTN, TRUE);
	this->changeToolBarBtnSelected(PAUSE_BTN, event->isPause());
	this->changeToolBarBtnSelected(DOT_BTN, event->getDotCount() == 1);
	this->changeToolBarBtnSelected(TRIPLE_BTN, event->getBeatTypeEx() == TRIPLE);
}

void MainForm::updateSetBeatTypeBtn() {
	Event* event = this->notesEditor->getSelectedEvent();
	UINT beatType = 1;
	for (UCHAR i = 0; i < 7; i++) {
		this->changeToolBarBtnEnabled(beatType, TRUE);
		this->changeToolBarBtnSelected(beatType, beatType == (UINT)event->getBeatType());
		beatType <<= 1;
	}
}

void MainForm::updateChangeTactBtn() {
	TactInfo* tactInfo = this->notesEditor->getSelectedTact();
	this->changeToolBarBtnEnabled(REPRISE_START_BTN, TRUE);
	this->changeToolBarBtnEnabled(REPRISE_END_BTN, TRUE);
	this->changeToolBarBtnSelected(REPRISE_START_BTN, tactInfo->repriseBegin);
	this->changeToolBarBtnSelected(REPRISE_END_BTN, tactInfo->repriseEnd > 1);
}

void MainForm::updatePlayBtn() {
	this->changeToolBarBtnEnabled(PLAY_BTN, this->notesEditor->getComposition()->isValid());
	this->changeToolBarBtnEnabled(STOP_BTN, FALSE);
	this->changeToolBarBtnEnabled(PAUSE_PLAY_BTN, FALSE);
}

void MainForm::updateChangeTrackBtn() {
	this->changeToolBarBtnEnabled(PREV_TRACK_BTN, TRUE);
	this->changeToolBarBtnEnabled(NEXT_TRACK_BTN, TRUE);
}

void MainForm::updateGuitarBtn() {
	Instrument* instrument = this->notesEditor->getSelectedTrack()->getInstrument();
	if (instrument->getInstrumentType() != GUITAR) {
		this->changeToolBarBtnEnabled(CHORD_UP_BTN, FALSE);
		this->changeToolBarBtnEnabled(CHORD_DOWN_BTN, FALSE);
		this->changeToolBarBtnEnabled(GUITAR_PROPERTIES_BTN, FALSE);
	} else {
		GuitarTrackEditor* trackEditor = reinterpret_cast<GuitarTrackEditor*>(this->notesEditor->getSelectedTrackEditor());
		GuitarEvent* guitarEvent = trackEditor->getSelectedGuitarEvent();
		if (guitarEvent->isPause()) {
			this->changeToolBarBtnEnabled(CHORD_UP_BTN, FALSE);
			this->changeToolBarBtnEnabled(CHORD_DOWN_BTN, FALSE);
		} else {
			this->changeToolBarBtnEnabled(CHORD_UP_BTN, TRUE);
			this->changeToolBarBtnEnabled(CHORD_DOWN_BTN, TRUE);
		}
		this->changeToolBarBtnEnabled(GUITAR_PROPERTIES_BTN, TRUE);
		this->changeToolBarBtnSelected(CHORD_UP_BTN, guitarEvent->getChordDirection() == UP);
		this->changeToolBarBtnSelected(CHORD_DOWN_BTN, guitarEvent->getChordDirection() == DOWN);
	}
}

void MainForm::updateMenuBtn() {

}

void MainForm::getViewComponent() {
	TrackViewComponent* trackView = this->notesEditor->getTrackViewComponent(&(this->viewInfo));
	this->trackViewComponent = trackView;
	if (trackView != NULL) {
		RECT rect;
		GetClientRect(this->hWnd, &rect);
		if (trackViewComponent->getSelectedViewComponent()->getY() > rect.bottom - rect.top) {
			trackView->move(trackView->getX(), trackViewComponent->getY() - trackViewComponent->getSelectedViewComponent()->getY()
				+ (rect.bottom - rect.top) / 2);
		}
	}
}

void MainForm::changeToolBarBtnEnabled(WORD button, BOOL enabled) {
	SendMessage(this->toolBar, TB_ENABLEBUTTON, button, enabled);
}

void MainForm::changeToolBarBtnSelected(WORD button, BOOL selected) {
	SendMessage(this->toolBar, TB_CHECKBUTTON, button, selected);
}

void MainForm::redraw() {
	RECT rect;
	GetClientRect(this->hWnd, &rect);
	InvalidateRect(this->hWnd, &rect, FALSE);
}

void MainForm::loadFile() {
	OPENFILENAME openFile;
	WCHAR szFile[100];
	ZeroMemory(&openFile, sizeof(openFile));
	openFile.lStructSize = sizeof(openFile);
	openFile.hwndOwner = NULL;
	openFile.lpstrFile = szFile;
	openFile.lpstrFile[0] = '\0';
	openFile.nMaxFile = sizeof(szFile);
	openFile.lpstrFilter = L"Guitar tab\0*.gt\0";
	openFile.nFilterIndex = 1;
	openFile.lpstrFileTitle = NULL;
	openFile.nMaxFileTitle = 0;
	openFile.lpstrInitialDir = NULL;
	openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&openFile)) {
		if (!this->notesEditor->loadComposition(openFile.lpstrFile)) {
			MessageBox(this->hWnd, L"Unable to load composition from this file", L"Error", 0);
		}
	}
}

void MainForm::saveFile() {
	if (this->notesEditor->getFileName() != L"") {
		this->notesEditor->saveComposition();
	} else {
		this->saveFileAs();
	}
}

void MainForm::saveFileAs() {
	OPENFILENAME openFile;
	WCHAR szFile[100];
	ZeroMemory(&openFile, sizeof(openFile));
	openFile.lStructSize = sizeof(openFile);
	openFile.hwndOwner = NULL;
	openFile.lpstrFile = szFile;
	openFile.lpstrFile[0] = '\0';
	openFile.nMaxFile = sizeof(szFile);
	openFile.lpstrFilter = L"Guitar tab\0*.gt\0";
	openFile.nFilterIndex = 1;
	openFile.lpstrFileTitle = NULL;
	openFile.nMaxFileTitle = 0;
	openFile.lpstrInitialDir = NULL;
	openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileName(&openFile)) {
		this->notesEditor->saveComposition(openFile.lpstrFile);
	}
}

void MainForm::updateWindowTitle() {
	if (this->notesEditor->getFileName() != L"") {
		wstring text = MAIN_FORM_DEFAULT_TITLE;
		SetWindowText(this->hWnd, (text + L" \"" + this->notesEditor->getFileName() + L"\"").c_str());
	}
}

void MainForm::processToolBarButtonClick(WORD button) {
	switch (button) {
	case WHOLE_BTN:
	case HALF_BTN:
	case QUATER_BTN:
	case EIGHTH_BTN:
	case SIXTEENTH_BTN:
	case THIRTY_SECOND_BTN:
	case SIXTY_FOURTH_BTN: {
		this->notesEditor->setBeatType((BeatType)button);
	} break;
	case DOT_BTN:
	case PAUSE_BTN:
	case TRIPLE_BTN: {
		this->processChangeEventButtons(button);
	} break;
	case REPRISE_START_BTN:
	case REPRISE_END_BTN: {
		this->processChangeTactButton(button);
	} break;
	case CHORD_UP_BTN:
	case CHORD_DOWN_BTN:
	case GUITAR_PROPERTIES_BTN: {
		this->processGuitarButton(button);
	}
	case PREV_TRACK_BTN:
	case NEXT_TRACK_BTN: {
		this->processChangeTrackButton(button);
	} break;
	case PLAY_BTN:
	case PAUSE_PLAY_BTN:
	case STOP_BTN: {
		this->processChangePlayingButton(button);
	} break;
	case ADD_TRACK_BTN: {
		CreateTrackDlg(this->hInstance, this->notesEditor, NULL, this->hWnd);
	} break;
	}
}

MainForm::UpdateFormCallback::UpdateFormCallback(MainForm * mainForm) {
	this->mainForm = mainForm;
}

void MainForm::UpdateFormCallback::call() {
	this->mainForm->update();
}
