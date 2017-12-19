#pragma once
#include "Windows.h"
#include "MainForm.h"
#include "FactoryOfTrackEditorFactoryImpl.h"
#include "Controls.h"

#define NOT_DEFINED_NAME L"Undefined"
#define DEFAULT_INSTRUMENT_TYPE GUITAR

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
	FactoryOfTrackEditorFactoryImpl* factory;
	Player* player;
	NotesEditor* notesEditor;

	wstring checkQuotes(wstring cmdLine);
};