#pragma once
#include "Windows.h"
#include "MainForm.h"
#include <vector>

using namespace std;

#define DEFAULT_COMPOSITION_NAME L"Undefined"

BOOL RegisterCustomWindowClasses(HINSTANCE hInstance);

INT_PTR CALLBACK CreateCompositionDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK EditCompositionDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK CreateTrackDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK EditTrackDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK ShowTracksDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CreateCompositionDlg(HINSTANCE hInstance, NotesEditor* notesEditor, HWND parent);

void EditCompositionDlg(HINSTANCE hInstance, NotesEditor* notesEditor, HWND parent);

void CreateTrackDlg(HINSTANCE hInstance, NotesEditor* notesEditor, CompositionInfo* compositionInfo, HWND parent);

void EditTrackDlg(HINSTANCE hInstance, NotesEditor* notesEditor, HWND parent);

void ShowTracksDlg(HINSTANCE hInstance, NotesEditor* notesEditor, HWND parent);