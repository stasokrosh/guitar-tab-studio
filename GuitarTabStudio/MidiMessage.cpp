#include "stdafx.h"
#include "MidiMessage.h"


MidiMessage MidiMessage::StartNoteMessage(UCHAR channel, UCHAR frequency, UCHAR velocity) {
	Message message;
	message.params[0] = 0x90 | channel;
	message.params[1] = frequency;
	message.params[2] = velocity;
	message.params[3] = 0;
	return MidiMessage(message);
}

MidiMessage MidiMessage::StopNoteMessage(UCHAR channel, UCHAR frequency, UCHAR velocity) {
	Message message;
	message.params[0] = 0x80 | channel;
	message.params[1] = frequency;
	message.params[2] = velocity;
	message.params[3] = 0;
	return MidiMessage(message);
}

MidiMessage MidiMessage::ChangeInstrumentMessage(UCHAR channel, UCHAR instrument) {
	Message message;
	message.params[0] = 0xC0 | channel;
	message.params[1] = instrument;
	message.params[2] = 0;
	message.params[3] = 0;
	return MidiMessage(message);
}

DWORD MidiMessage::getMessage() {
	return this->message.fullMessage;
}

MidiMessage::MidiMessage(Message message) {
	this->message = message;
}

MidiMessage::MidiMessage() {}

MidiMessage::~MidiMessage() {}

