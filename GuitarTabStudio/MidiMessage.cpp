#include "stdafx.h"
#include "MidiMessage.h"


MidiMessage MidiMessage::startNoteMessage(UCHAR channel, UCHAR frequency, UCHAR velocity) {
	Message message;
	return MidiMessage(message);
}

MidiMessage MidiMessage::stopNoteMessage(UCHAR channel, UCHAR frequency) {
	Message message;
	return MidiMessage(message);
}

MidiMessage MidiMessage::changeInstrumentMessage(UCHAR channel, UCHAR instrument) {
	Message message;
	return MidiMessage(message);
}

ULONG MidiMessage::getMessage() {
	return this->message.fullMessage;
}

MidiMessage::MidiMessage(Message message) {
	this->message = message;
}
