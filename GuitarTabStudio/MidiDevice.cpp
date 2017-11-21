#include "stdafx.h"
#include "MidiDevice.h"


MidiDevice::MidiDevice() {
	closed = true;
}

BOOL MidiDevice::open() {
	UCHAR midiDeviceCount = midiOutGetNumDevs();
	UCHAR i = 0;
	while (i < midiDeviceCount && midiOutOpen(&hMidi, i, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
		i++;
	}
	return i != midiDeviceCount;
}

void MidiDevice::close() {
	if (!closed) {
		midiOutClose(hMidi);
		closed = TRUE;
	}
}

void MidiDevice::sendMessage(MidiMessage midiMessage) {
	midiOutShortMsg(hMidi, midiMessage.getMessage());
}


MidiDevice::~MidiDevice() {
	close();
}
