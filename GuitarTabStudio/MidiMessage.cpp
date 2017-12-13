#include "stdafx.h"
#include "MidiMessage.h"


MidiMessage MidiMessage::StartNoteMessage(UCHAR channel, UCHAR frequency, UCHAR velocity) {
	Message message;
	return MidiMessage(message);
}

MidiMessage MidiMessage::StopNoteMessage(UCHAR channel, UCHAR frequency) {
	Message message;
	return MidiMessage(message);
}

MidiMessage MidiMessage::ChangeInstrumentMessage(UCHAR channel, UCHAR instrument) {
	Message message;
	return MidiMessage(message);
}

ULONG MidiMessage::getMessage() {
	return this->message.fullMessage;
}

MidiMessage::MidiMessage(Message message) {
	this->message = message;
}

MidiMessage::MidiMessage() {}
