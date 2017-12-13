#pragma once
#include "MidiMessage.h"
#include "MidiDevice.h"

#include "Track.h"
#include "NotesEditor.h"

#include <vector>

using namespace std;

class MidiTrack {
public:
	MidiTrack(UCHAR channel, UCHAR instrumentNum, NotesEditor* notesEditor, MidiDevice* midiDevice, vector<MidiEvent*>* events);
	~MidiTrack();
	void initialize();
	MidiEvent* getCurrentEvent();
	BOOL play();
private:
	MidiMessage initializeMessage;
	vector<MidiEvent*>* events;
	MidiDevice* midiDevice;
	NotesEditor* notesEditor;
};

