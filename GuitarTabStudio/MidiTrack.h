#pragma once
#include "MidiMessage.h"
#include "MidiDevice.h"

#include "Track.h"
#include "Callback.h"

#include <vector>

using namespace std;

class MidiTrack{
public:
	MidiTrack(UCHAR channel, Track* track, MidiDevice* midiDevice, vector<MidiEvent*>* events);
	~MidiTrack();
	void initialize();
	Track* getTrack();
	MidiEvent* getCurrentEvent();
	void setChangeNoteCallback(Callback* changeNoteCallback);
	BOOL play();
private:
	MidiMessage* initializeMessage;
	vector<MidiEvent*>* events;
	Track* track;
	Callback* changeNoteCallback;
	MidiDevice* midiDevice;
};

