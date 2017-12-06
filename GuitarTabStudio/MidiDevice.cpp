#include "stdafx.h"
#include "MidiDevice.h"


MidiDevice::MidiDevice() {
	UCHAR midiDeviceCount = midiOutGetNumDevs();
	UCHAR i = 0;
	while (i < midiDeviceCount && midiOutOpen(&hMidi, i, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
		i++;
	}
	if (i != midiDeviceCount) {
		throw exception("No midi devices available");
	}
}

void MidiDevice::sendMessage(MidiMessage* midiMessage) {
	midiOutShortMsg(hMidi, midiMessage->getMessage());
}


MidiDevice::~MidiDevice() {
	midiOutClose(hMidi);
}
