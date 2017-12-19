#pragma once
#include <Windows.h>
#include <string>

using namespace std;

#define OCTAVE_SIZE 12

union Message {
	DWORD fullMessage;
	UCHAR params[4];
};

enum Notes {
	C,
	Db,
	D,
	Eb,
	E,
	F,
	Gb,
	G,
	Ab,
	A,
	Hb,
	H
};

UCHAR GetFrequency(UCHAR octave, Notes note);

struct Note {
	Notes frequency;
	UCHAR octave;
};

wstring NoteToWstring(Notes note);
