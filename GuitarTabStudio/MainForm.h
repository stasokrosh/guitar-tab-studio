#pragma once
#include "resource.h"
#include "Windows.h"
#include "Commctrl.h"
#include "Commdlg.h"
#include "Timer.h"
#include "NotesEditor.h"
#include "ViewInfo.h"
#include "Player.h"
#include "GuitarTrackEditor.h"
#include "TrackViewComponent.h"
#include "Drawing.h"
#include "Controls.h"

#define MAIN_FORM_CLASS_NAME L"MainForm"
#define MAIN_FORM_DEFAULT_TITLE L"GuitarTabStudio"

#define TOOLBAR_BTN_COUNT 24

#define WHOLE_BTN 1
#define HALF_BTN 2
#define DOT_BTN 3
#define QUATER_BTN 4
#define PAUSE_BTN 5
#define REPRISE_START_BTN 6
#define REPRISE_END_BTN 7
#define EIGHTH_BTN 8
#define CHORD_DOWN_BTN 9
#define CHORD_UP_BTN 10
#define GUITAR_PROPERTIES_BTN 11
#define TRIPLE_BTN 12
#define PLAY_BTN 13
#define PAUSE_PLAY_BTN 14
#define STOP_BTN 15
#define SIXTEENTH_BTN 16
#define NEXT_TRACK_BTN 17
#define PREV_TRACK_BTN 18
#define ADD_TRACK_BTN 19
#define THIRTY_SECOND_BTN 32
#define SIXTY_FOURTH_BTN 64

class MainForm {
public:
	MainForm(HINSTANCE hInstance);
	~MainForm();
	void Show();
	HWND getHWND();
	Timer* getTimer();
	void update();
	void setNotesEditor(NotesEditor* notesEditor);
	void setPlayer(Player* player);
	Callback* getUpdateFormCallback();
	void processToolBarButtonClick(WORD button);
	void processMenuButtonClick(WORD button);
	void processKeyUp(WORD key);
	void processClick(WORD x, WORD y);
	void processControlClick(WORD x, WORD y);
	void processWheel(DWORD lParam, DWORD wParam);
	void processSizing();
	void draw(HDC hdc);

	static BOOL RegisterMainFormClass(HINSTANCE hInstance);
private:
	HWND hWnd;
	HINSTANCE hInstance;
	Timer* timer;
	WORD toolBarHeight;
	HWND toolBar;
	NotesEditor* notesEditor;
	Player* player;
	ViewInfo viewInfo;
	TrackViewComponent* trackViewComponent;

	HWND CreateToolBar();
	void processChangeEventButtons(WORD button);
	void processChangeTactButton(WORD button);
	void processChangeTrackButton(WORD button);
	void processGuitarButton(WORD button);
	void processChangePlayingButton(WORD button);
	void updateToolbarBtn();
	void updateChangeEventBtn();
	void updateSetBeatTypeBtn();
	void updateChangeTactBtn();
	void updatePlayBtn();
	void updateChangeTrackBtn();
	void updateGuitarBtn();
	void updateMenuBtn();
	void getViewComponent();
	void changeToolBarBtnEnabled(WORD button, BOOL enabled);
	void changeToolBarBtnSelected(WORD button, BOOL selected);
	void redraw();
	void loadFile();
	void saveFile();
	void saveFileAs();
	void updateWindowTitle();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	class UpdateFormCallback : public Callback {
	public:
		UpdateFormCallback(MainForm* mainForm);
		virtual void call();
	private:
		MainForm* mainForm;
	};
};

