#include "stdafx.h"
#include "TrackEditor.h"


TrackEditor::TrackEditor(Track* track, Callback* updateCallback) {
	this->track = track;
	this->selectedEvent = NULL;
	this->updateCallback = updateCallback;
}


TrackEditor::~TrackEditor() {
	delete this->track;
}

Track * TrackEditor::getTrack() {
	return this->track;
}

void TrackEditor::setSelectedEvent(SelectedEvent* selectedEvent) {
	this->selectedEvent = selectedEvent;
}

MidiTrack* TrackEditor::getMidiTrack(UCHAR channel, MidiDevice* midiDevice, TactInfo* tact, BOOL selected) {
	TactIterator* current = this->getTactByTactInfo(tact);
	TactIterator* begin = this->track->getBegin();
	TactIterator* end = this->track->getEnd();
	vector<MidiEvent*>* events = new vector<MidiEvent*>();
	vector<pair<Tact*, UCHAR>> repriseStack;
	while (!current->equal(end)) {
		this->addMidiEventsToVector(current, channel,events, selected);
		if (repriseStack.size() > 0) {
			pair<Tact*, UCHAR> currentReprise = repriseStack.back();
			if (current->getTact() == currentReprise.first) {
				currentReprise.second--;
				if (currentReprise.second == 0) {
					repriseStack.pop_back();
					current->moveForward();
				} else {
					TrackEditor::MoveSelectorBack(current, begin);
				}
			} else {
				TrackEditor::CreateNewReprise(current, begin, &repriseStack);
			}
		} else {
			TrackEditor::CreateNewReprise(current, begin, &repriseStack);
		}
	}
	delete current;
	delete begin;
	delete end;
	return new MidiTrack(channel, this->track->getInstrument()->getNumber(), midiDevice, events);
}

TactIterator* TrackEditor::getTactByTactInfo(TactInfo* tactInfo) {
	TactIterator* tactIterator = this->track->getBegin();
	TactIterator* endTactIterator = this->track->getEnd();
	while (!tactIterator->equal(endTactIterator)){		
		if (tactIterator->getTact()->getTactInfo() == tactInfo) {
			delete endTactIterator;
			return tactIterator;
		}
		tactIterator->moveForward();
	}
	delete tactIterator;
	delete endTactIterator;
}

TactIterator* TrackEditor::getTactByEvent(EventIterator* eventIterator) {
	TactIterator* tactIterator = this->track->getBegin();
	TactIterator* endTactIterator = this->track->getEnd();
	while (!tactIterator->equal(endTactIterator)) {
		Tact* tact = tactIterator->getTact();
		EventIterator* tactEventIterator = tact->getBegin();
		EventIterator* endEventIterator = tact->getEnd();
		while (!tactEventIterator->equal(endEventIterator)) {
			if (eventIterator->getEvent() == tactEventIterator->getEvent()) {
				delete endTactIterator;
				delete tactEventIterator;
				delete endEventIterator;
				return tactIterator;
			}
		}
		delete eventIterator;
		delete endEventIterator;
	}
	delete tactIterator;
	delete endTactIterator;
}

void TrackEditor::addMidiEventsToVector(TactIterator* iterator, UCHAR channel,vector<MidiEvent*>* events, BOOL selected) {
	EventIterator* eventIterator = iterator->getTact()->getBegin();
	EventIterator* endIterator = iterator->getTact()->getEnd();
	while (!eventIterator->equal(endIterator)) {
		Event* event = eventIterator->getEvent();
		Callback* changeNoteCallback;
		if (selected) {
			changeNoteCallback = new SelectedEvent::SelectEventCallback(this->selectedEvent, eventIterator->copy());
		} else {
			changeNoteCallback = NULL;
		}
		events->push_back(this->getMidiEvent(event, channel, changeNoteCallback));
	}
	delete eventIterator;
	delete endIterator;
}

void TrackEditor::MoveSelectorBack(TactIterator* current, TactIterator* begin) {
	while (!current->equal(begin) && !current->getTact()->getTactInfo()->repriseBegin) {
		current->moveBackwards();
	}
}

void TrackEditor::CreateNewReprise(TactIterator* current, TactIterator* begin, vector<pair<Tact*, UCHAR>>* repriseStack) {
	if (current->getTact()->getTactInfo()->repriseEnd > 1) {
		pair<Tact*, UCHAR> newReprise(current->getTact(), current->getTact()->getTactInfo()->repriseEnd - 1);
		repriseStack->push_back(newReprise);
		TrackEditor::MoveSelectorBack(current, begin);
	} else {
		current->moveForward();
	}
}



