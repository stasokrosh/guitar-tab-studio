#include "stdafx.h"
#include "Application.h"


Application::Application(HINSTANCE hInstance, LPWSTR cmdLine) {
	this->hInstance = hInstance;
	this->cmdLine = cmdLine;
	this->factory = NULL;
	this->mainForm = NULL;
	this->notesEditor = NULL;
	this->player = NULL;
}

Application::~Application() {
	if (this->mainForm != NULL) {
		delete this->mainForm;
	}
	if (this->factory != NULL) {
		delete this->factory;
	}
	if (this->player != NULL) {
		delete this->player;
	}
	if (this->notesEditor != NULL) {
		delete this->notesEditor;
	}
}

BOOL Application::initialize() {
	if (!RegisterCustomWindowClasses(this->hInstance)) {
		return FALSE;
	}
	this->mainForm = new MainForm(this->hInstance);
	this->factory = new FactoryOfTrackEditorFactoryImpl();
	if (!this->factory->initialize()) {
		MessageBox(this->mainForm->getHWND(), L"File\"guitars.ini\" was not found", L"Error", 0);
		return FALSE;
	}
	this->notesEditor = new NotesEditor(this->factory, this->mainForm->getUpdateFormCallback());
	this->mainForm->setNotesEditor(this->notesEditor);
	try {
		this->player = new Player(this->mainForm->getTimer(), this->notesEditor, this->mainForm->getUpdateFormCallback());
	}
	catch (exception e) {
		MessageBox(this->mainForm->getHWND(), L"Free MIDI devices are not found", L"Error", 0);
		return FALSE;
	}
	this->mainForm->setPlayer(this->player);
	if ((wstring)this->cmdLine == (wstring)L"") {
		CompositionInfo compositionInfo;
		compositionInfo.name = NOT_DEFINED_NAME;
		this->notesEditor->createComposition(compositionInfo);
		TrackEditorFactory* factory = this->factory->getTrackEditorFactory(DEFAULT_INSTRUMENT_TYPE);
		vector<wstring> names = factory->getInstrumentNames();
		TrackInfo trackInfo;
		trackInfo.name = NOT_DEFINED_NAME;
		notesEditor->addTrack(trackInfo, DEFAULT_INSTRUMENT_TYPE, names.at(0));
	} else {
		if (!this->notesEditor->loadComposition(this->checkQuotes(this->cmdLine))) {
			MessageBox(this->mainForm->getHWND(), L"This file can't be opened", L"Error", 0);
			return FALSE;
		}
	}
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
}

wstring Application::checkQuotes(wstring cmdLine) {
	if (cmdLine.front() == L'\"' && cmdLine.back() == L'\"') {
		cmdLine.pop_back();
		cmdLine.erase(cmdLine.begin());
	}
	return cmdLine;
}
