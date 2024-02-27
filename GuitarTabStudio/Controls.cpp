#include "stdafx.h"
#include "Controls.h"


BOOL RegisterCustomWindowClasses(HINSTANCE hInstance) {
	INITCOMMONCONTROLSEX init;
	init.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&init);
	if (!MainForm::RegisterMainFormClass(hInstance)) {
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK CreateCompositionDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"4/4");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"3/4");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"7/8");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), DEFAULT_COMPOSITION_NAME);
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT3), to_wstring(DEFAULT_TEMPO).c_str());
		SetWindowText(hDlg, L"Create composition");
	} break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: {
			CompositionInfo* compositionInfo = new CompositionInfo();
			WORD cursel = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			if (cursel == 1) {
				compositionInfo->tactDuration.beatCount = 3;
			} else {
				if (cursel == 2) {
					compositionInfo->tactDuration.beatCount = 7;
					compositionInfo->tactDuration.beatType = EIGHTH;
				}
			}
			WCHAR text[100];
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), text, 100);
			compositionInfo->name = text;
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT2), text, 100);
			compositionInfo->author = text;
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT3), text, 100);
			NotesEditor* editor = (NotesEditor*)GetWindowLongPtr(hDlg, GWLP_USERDATA);
			try {
				UCHAR tempo = stoi(text);
				compositionInfo->tempo = tempo;
				CreateTrackDlg(GetModuleHandle(NULL), editor, compositionInfo, hDlg);
			}
			catch (exception e) {
				MessageBox(hDlg, L"Wrong input", L"Error", 0);
			}
			DestroyWindow(hDlg);
			return TRUE;
		} break;
		}
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

INT_PTR CALLBACK EditCompositionDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		NotesEditor* editor = (NotesEditor*)lParam;
		Composition* composition = editor->getComposition();
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"4/4");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"3/4");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)L"7/8");
		WORD cursel = 0;
		if (composition->getTactDuration()->beatCount == 3 && composition->getTactDuration()->beatType == QUATER) {
			cursel = 1;
		}
		if (composition->getTactDuration()->beatCount == 7 && composition->getTactDuration()->beatType == EIGHTH) {
			cursel = 2;
		}
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, cursel, 0);
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), composition->getName().c_str());
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT2), composition->getAuthor().c_str());
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT3), to_wstring(composition->getTempo()).c_str());
		SetWindowText(hDlg, L"Edit composition");
		SetWindowText(GetDlgItem(hDlg, IDC_BUTTON1), L"Save changes");
	} break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: {
			CompositionInfo* compositionInfo = new CompositionInfo();
			WORD cursel = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			if (cursel == 1) {
				compositionInfo->tactDuration.beatCount = 3;
			} else {
				if (cursel == 2) {
					compositionInfo->tactDuration.beatCount = 7;
					compositionInfo->tactDuration.beatType = EIGHTH;
				}
			}
			WCHAR text[100];
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), text, 100);
			compositionInfo->name = text;
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT2), text, 100);
			compositionInfo->author = text;
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT3), text, 100);
			NotesEditor* editor = (NotesEditor*)GetWindowLongPtr(hDlg, GWLP_USERDATA);
			try {
				UCHAR tempo = stoi(text);
				compositionInfo->tempo = tempo;
				editor->setCompositionInfo(compositionInfo);
			}
			catch (exception e) {
				MessageBox(hDlg, L"Wrong input", L"Error", 0);
			}
			delete compositionInfo;
			DestroyWindow(hDlg);
			return TRUE;
		} break;
		}
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

INT_PTR CALLBACK CreateTrackDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		NotesEditor* editor = (NotesEditor*)lParam;
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), DEFAULT_COMPOSITION_NAME);
		FactoryOfTrackEditorFactory* factory = editor->getFactory();
		TrackEditorFactory* trackEditorFactory = factory->getTrackEditorFactory(GUITAR);
		vector<wstring> names = trackEditorFactory->getInstrumentNames();
		for (wstring name : names) {
			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)(name.c_str()));
		}
	} break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: {
			TrackInfo trackInfo;
			NotesEditor* editor = (NotesEditor*)GetWindowLongPtr(hDlg, GWLP_USERDATA);
			WORD cursel = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
			FactoryOfTrackEditorFactory* factory = editor->getFactory();
			TrackEditorFactory* trackEditorFactory = factory->getTrackEditorFactory(GUITAR);
			vector<wstring> names = trackEditorFactory->getInstrumentNames();
			wstring name = names.at(cursel);
			WCHAR text[100];
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), text, 100);
			trackInfo.name = text;
			editor->addTrack(trackInfo, GUITAR, name);
			DestroyWindow(hDlg);
			return TRUE;
		} break;
		}
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

INT_PTR CALLBACK EditTrackDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		NotesEditor* editor = (NotesEditor*)lParam;
		Track* track = editor->getSelectedTrack();
		TrackEditor* trackEditor = editor->getSelectedTrackEditor();
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), track->getName().c_str());
		WORD controlMaxPos = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETRANGEMAX, 0, 0);
		WORD controlMinPos = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETRANGEMIN, 0, 0);
		WORD width = controlMaxPos - controlMinPos;
		SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETPOS, 0, width * 127 / track->getVelocity());
	} break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: {
			TrackInfo trackInfo;
			NotesEditor* editor = (NotesEditor*)GetWindowLongPtr(hDlg, GWLP_USERDATA);
			TrackEditor* trackEditor = editor->getSelectedTrackEditor();
			WCHAR text[100];
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), text, 100);
			trackInfo.name = text;
			WORD controlMaxPos = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETRANGEMAX, 0, 0);
			WORD controlMinPos = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETRANGEMIN, 0, 0);
			WORD width = controlMaxPos - controlMinPos;
			WORD pos = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETPOS, 0, 0);
			trackInfo.velocity = 127 * pos / width;
			trackEditor->setTrackInfo(&trackInfo);
			DestroyWindow(hDlg);
			return TRUE;
		} break;
		}
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

INT_PTR CALLBACK ShowTracksDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		NotesEditor* editor = (NotesEditor*)lParam;
		vector<Track*> tracks = editor->getTracks();
		for (Track* track : tracks) {
			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)track->getName().c_str());
		}
	} break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: {
			DestroyWindow(hDlg);
			return TRUE;
		} break;
		case IDC_LIST1: {
			NotesEditor* editor = (NotesEditor*)GetWindowLongPtr(hDlg, GWLP_USERDATA);
			vector<Track*> tracks = editor->getTracks();
			auto cursel = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
			if (cursel < 0)
				return FALSE;
			Track* track = tracks.at(cursel);
			editor->selectTrack(track);
			DestroyWindow(hDlg);
			return TRUE;
		} break;
		}
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

void CreateCompositionDlg(HINSTANCE hInstance, NotesEditor * notesEditor, HWND parent) {
	HWND dlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_PROPPAGE_MEDIUM), parent, CreateCompositionDialogProc, 0);
	SetWindowLongPtr(dlg, GWLP_USERDATA, (LONG_PTR)notesEditor);
	ShowWindow(dlg, 1);
	MSG msg;
	while ((GetMessage(&msg, 0, 0, 0)) != 0) {
		if (!IsDialogMessage(dlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void EditCompositionDlg(HINSTANCE hInstance, NotesEditor * notesEditor, HWND parent) {
	HWND dlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_PROPPAGE_MEDIUM), parent, EditCompositionDialogProc, (LPARAM)notesEditor);
	SetWindowLongPtr(dlg, GWLP_USERDATA, (LONG_PTR)notesEditor);
	ShowWindow(dlg, 1);
	MSG msg;
	while ((GetMessage(&msg, 0, 0, 0)) != 0) {
		if (!IsDialogMessage(dlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CreateTrackDlg(HINSTANCE hInstance, NotesEditor * notesEditor, CompositionInfo* compositionInfo, HWND parent) {
	if (compositionInfo != NULL) {
		notesEditor->createComposition(*compositionInfo);
	}
	HWND dlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_PROPPAGE_LARGE), parent, CreateTrackDialogProc, (LPARAM)notesEditor);
	SetWindowLongPtr(dlg, GWLP_USERDATA, (LONG_PTR)notesEditor);
	ShowWindow(dlg, 1);
	MSG msg;
	while ((GetMessage(&msg, 0, 0, 0)) != 0) {
		if (!IsDialogMessage(dlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void EditTrackDlg(HINSTANCE hInstance, NotesEditor * notesEditor, HWND parent) {
	HWND dlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_PROPPAGE_MEDIUM1), parent, EditTrackDialogProc, (LPARAM)notesEditor);
	SetWindowLongPtr(dlg, GWLP_USERDATA, (LONG_PTR)notesEditor);
	ShowWindow(dlg, 1);
	MSG msg;
	while ((GetMessage(&msg, 0, 0, 0)) != 0) {
		if (!IsDialogMessage(dlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void ShowTracksDlg(HINSTANCE hInstance, NotesEditor * notesEditor, HWND parent) {
	HWND dlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_PROPPAGE_MEDIUM2), parent, ShowTracksDialogProc, (LPARAM)notesEditor);
	SetWindowLongPtr(dlg, GWLP_USERDATA, (LONG_PTR)notesEditor);
	ShowWindow(dlg, 1);
	MSG msg;
	while ((GetMessage(&msg, 0, 0, 0)) != 0) {
		if (!IsDialogMessage(dlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
