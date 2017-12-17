#include "stdafx.h"
#include "Midi.h"

UCHAR GetFrequency(UCHAR octave, Notes note) {
	return octave * OCTAVE_SIZE + note;
}

wstring NoteToWstring(Notes note) {
	switch (note) {
		case C: {
			return L"C";
		} break;
		case Db: {
			return L"Db";
		} break;
		case D: {
			return L"D";
		} break;
		case Eb: {
			return L"Eb";
		} break;
		case E: {
			return L"E";
		} break;
		case F: {
			return L"F";
		} break;
		case Gb: {
			return L"Gb";
		} break;
		case G: {
			return L"G";
		} break;
		case Ab: {
			return L"Ab";
		} break;
		case A: {
			return L"A";
		} break;
		case Hb: {
			return L"Hb";
		} break;
		case H: {
			return L"H";
		} break;
	}
}
