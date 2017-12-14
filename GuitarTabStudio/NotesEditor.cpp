#include "stdafx.h"
#include "NotesEditor.h"


NotesEditor::NotesEditor(FactoryOfTrackEditorFactory* factoryOfTEFactory) {
	this->factoryOfTEFactory = factoryOfTEFactory;
	this->selectedTrackEditor = NULL;
	this->selectedTact = NULL;
	this->selectedEvent = NULL;
	this->tactSelected = FALSE;
	this->fileName = L"";
}

void NotesEditor::createComposition(CompositionInfo compositionInfo) {
	this->composition = new Composition(compositionInfo);
}

BOOL NotesEditor::loadComposition(wstring name) {
	wifstream stream;
	try {
		stream.open(name);
		CompositionInfo compositionInfo;
		if (!ReadCompositionInfo(&stream, &compositionInfo)) {
			return FALSE;
		}
		this->composition = new Composition(compositionInfo);
		wstring text;
		ReadLine(&stream, &text);
		USHORT tactCount = stoi(text);
		vector<TactInfo*> tacts;
		for (USHORT i = 0; i < tactCount; i++) {
			TactInfo* tactInfo = new TactInfo(&compositionInfo.tactDuration);
			if (!ReadTactInfo(&stream, tactInfo)) {
				return FALSE;
			}
			this->composition->pushTactInfo(tactInfo);
			tacts.push_back(tactInfo);
		}
		ReadLine(&stream, &text);
		USHORT trackCount = stoi(text);
		for (USHORT i = 0; i < trackCount; i++) {
			ReadLine(&stream, &text);
			BOOL selected = (BOOL)stoi(text);
			TrackInfo trackInfo;
			if (!ReadTrackInfo(&stream, &trackInfo)) {
				return FALSE;
			}
			wstring name;
			Instruments type;
			if (!ReadInstrumentInfo(&stream, &name, &type)) {
				return FALSE;
			}
			TrackEditorFactory* factory = this->factoryOfTEFactory->getTrackEditorFactory(type);
			TrackEditor* trackEditor = factory->createTrackEditor(name, trackInfo, this);
			if (trackEditor == NULL) {
				return FALSE;
			}
			this->trackEditors.push_back(trackEditor);
			if (selected) {
				this->selectedTrackEditor = trackEditor;
			}
			if (!trackEditor->Load(&stream, &tacts, &(this->selectedTact), &(this->selectedEvent))) {
				return FALSE;
			}
		}
		stream.close();
		return TRUE;
	} catch (exception e) {
		if (stream.open) {
			stream.close();
		}
		return FALSE;
	}
}

void NotesEditor::saveComposition(wstring name) {
	wofstream stream(name);
	WriteCompositionInfo(&stream, this->composition->getCompositionInfo());
	USHORT tactInfoCount = this->composition->getTactInfoCount();
	WriteLine(&stream, to_wstring(tactInfoCount));
	for (USHORT i = 0; i < tactInfoCount; i++) {
		WriteTactInfo(&stream, this->composition->getTactInfo(i));
	}
	WriteLine(&stream, to_wstring(this->composition->getSize()));
	for (TrackEditor* trackEditor : this->trackEditors) {
		if (trackEditor == this->selectedTrackEditor) {
			WriteLine(&stream, to_wstring(TRUE));
		} else {
			WriteLine(&stream, to_wstring(FALSE));
		}
		WriteTrackInfo(&stream, trackEditor->getTrack()->getTrackInfo());
		WriteInstrument(&stream, trackEditor->getTrack()->getInstrument());
		trackEditor->Write(&stream);
	}
	stream.close();
}

void NotesEditor::saveComposition() {
	this->saveComposition(this->fileName);
}

wstring NotesEditor::getFileName() {
	return this->fileName;
}

BOOL NotesEditor::addTrack(TrackInfo trackInfo, Instruments instrumentType, wstring instrumentName) {
	TrackEditorFactory* trackEditorFactory = this->factoryOfTEFactory->getTrackEditorFactory(instrumentType);
	if (trackEditorFactory == NULL) {
		return FALSE;
	} else {
		TrackEditor* trackEditor = trackEditorFactory->createTrackEditor(instrumentName, trackInfo, this);
		if (trackEditor == NULL) {
			return FALSE;
		} else {
			this->composition->addTrack(trackEditor->getTrack());
			this->trackEditors.push_back(trackEditor);
			if (this->composition->getSize() == 1) {
				this->composition->pushTactInfo(new TactInfo(this->composition->getTactDuration()));
			}
			TrackEditor* trackEditor = this->trackEditors.back();
			vector<EventInfo> events = NotesEditor::GetEventsForTactDuration(this->composition->getTactDuration);
			for (int i = 0; i < this->composition->getTactInfoCount(); i++) {
				this->addEmptyTact(trackEditor->getTrack(), events, this->composition->getTactInfo(i));
			}
			this->selectTrackEditor(trackEditor);
			return TRUE;
		}
	}
}

NotesEditor::~NotesEditor() {
	this->clearComposition();
}

Composition * NotesEditor::getComposition() {
	return this->composition;
}

MidiComposition * NotesEditor::createMidiComposition(MidiDevice * midiDevice) {
	if (!this->composition->isValid()) {
		return FALSE;
	}
	TactInfo* selectedTactInfo = this->getSelectedTact()->getTactInfo();
	set<UCHAR>* channelSet = this->validateChannelRelation();
	if (!channelSet) {
		return NULL;
	}
	MidiTrack** tracks = new MidiTrack*[this->composition->getSize()];
	UCHAR notPreferredChannelBeginValue = 0;
	int i = 0;
	while (i < this->composition->getSize()) {
		Track* track = this->composition->getTrack(i);
		UCHAR preferedChannel = track->getInstrument()->getPreferedChannel();
		if (preferedChannel == -1) {
			notPreferredChannelBeginValue = NotesEditor::FindMinValueNotInSet(notPreferredChannelBeginValue, channelSet);
			preferedChannel = notPreferredChannelBeginValue;
			notPreferredChannelBeginValue++;
		}
		tracks[i] = track->getMidiTrack(this, preferedChannel, midiDevice, selectedTactInfo, NULL);
		i++;
	}
	return new MidiComposition(midiDevice, this->composition->getTempo(), tracks, this->composition->getSize());
}

vector<Track*> NotesEditor::getTracks() {
	vector<Track*> result;
	for (int i = 0; i < this->composition->getSize(); i++) {
		result.push_back(this->composition->getTrack(i));
	}
	return result;
}

EventInfo  NotesEditor::getEventInfo() {
	return this->eventInfo;
}

void NotesEditor::deleteTrack(Track * track) {
	vector<TrackEditor*>::iterator iterator = this->findTrackEditorIteratorByTrack(track);
	if (iterator != this->trackEditors.end()) {
		this->trackEditors.erase(iterator, iterator);
	}
	this->selectTrack(this->composition->getTrack(0));
}

void NotesEditor::selectTrack(Track * track) {
	if (this->getSelectedEvent()->isEmpty()) {
		this->setEventPause();
	}
	TrackEditor* trackEditor = this->findTrackEditorByTrack(track);
	if (trackEditor != NULL) {
		this->selectTrackEditor(trackEditor);
	}
}

void NotesEditor::selectTact(Tact* tact) {
	Track* track = tact->getTrack();
	this->selectTrack(track);
	this->selectedTrackEditor->getIteratorByTactInfo(tact->getTactInfo(), &(this->selectedTact));
	this->selectedEvent = this->getSelectedTact()->getBegin();
	this->setTactSelected(TRUE);
}

void NotesEditor::selectEvent(Event * event) {
	Track* track = event->getTact()->getTrack();
	TactInfo* tactInfo = event->getTact()->getTactInfo();
	this->selectTrack(track);
	this->selectedTrackEditor->getIteratorsByEvent(tactInfo, &(this->selectedTact), &(this->selectedEvent));
}

void NotesEditor::setEventPause() {
	this->getSelectedEvent()->setPause(TRUE);
}

Track * NotesEditor::getSelectedTrack() {
	return this->selectedTrackEditor->getTrack();
}

void NotesEditor::moveForward() {
	if (this->getSelectedEvent()->isEmpty()) {
		if (this->getSelectedTact()->getSize() == 1) {
			this->setEventPause();
		} else {
			this->selectedEvent->deleteEvent();
		}
		if (this->selectedEvent->isLast()) {
			this->moveNextTact();
		}
	} else {
		if (this->selectedEvent->isLast()) {
			this->selectedEvent->insertEvent(this->eventInfo);
			this->selectedEvent->moveForward();
			this->getSelectedEvent()->setEmpty();
		} else {
			this->selectedEvent->moveForward();
		}
	} 
}

void NotesEditor::moveBackward() {
	if (this->getSelectedEvent()->isEmpty()) {
		if (this->getSelectedTact()->getSize() == 1) {
			this->getSelectedEvent()->setPause(TRUE);
		} else {
			this->selectedEvent->deleteEvent();
		}
		if (this->selectedEvent->isFirst()) {
			this->movePrevTact();
		}
	} else {
		if (this->selectedEvent->isFirst()) {
			this->movePrevTact();
		} else {
			this->selectedEvent->moveBackwards();
		}
	}
}

void NotesEditor::addEmptyTact(Track * track, vector<EventInfo> events, TactInfo* tactInfo) {
	Tact* tact = track->pushTact(tactInfo)->getTact();
	for (EventInfo eventInfo : events) {
		tact->pushEvent(eventInfo);
	}
}

void NotesEditor::moveNextTact() {
	if (this->selectedTact->isLast()) {
		TactInfo* tactInfo = new TactInfo(this->composition->getTactDuration());
		this->composition->pushTactInfo(tactInfo);
		vector<EventInfo> events = NotesEditor::GetEventsForTactDuration(this->composition->getTactDuration);
		for (int i = 0; i < this->composition->getSize(); i++) {
			this->addEmptyTact(this->composition->getTrack(i), events, tactInfo);
		}
	}
	this->selectedTact->moveForward();
	this->selectedEvent = this->getSelectedTact()->getBegin();
}

void NotesEditor::movePrevTact() {
	if (!this->selectedTact->isFirst()) {
		if (this->selectedTact->isLast) {
			if (this->emptyEnding()) {
				this->deleteEnding();
			}
		}
		this->selectedTact->moveBackwards();
		this->selectedEvent = this->getSelectedTact()->getEnd();
		this->selectedEvent->moveBackwards();
	}
}

void NotesEditor::setTactSelected(BOOL tactSelected) {
	this->tactSelected = tactSelected;
}

set<UCHAR>* NotesEditor::validateChannelRelation() {
	set<UCHAR>* channelSet = new set<UCHAR>();
	UCHAR i = 0;
	while (i < this->composition->getSize()) {
		UCHAR preferedChannel = this->composition->getTrack(i)->getInstrument()->getPreferedChannel();
		if (preferedChannel != -1) {
			std::pair<set<UCHAR>::iterator, bool> pair = channelSet->insert(preferedChannel);
			if (!pair.second) {
				delete channelSet;
				return NULL;
			}
		}
	}
	return channelSet;
}

void NotesEditor::selectTrackEditor(TrackEditor * trackEditor) {
	TactInfo* tactInfo;
	if (this->selectedTact == NULL) {
		tactInfo = this->composition->getTactInfo(0);
	} else {
		tactInfo = this->getSelectedTact()->getTactInfo();
	}
	this->selectedTrackEditor = trackEditor;
	selectedTrackEditor->getIteratorByTactInfo(tactInfo, &(this->selectedTact));
	this->selectedEvent = this->getSelectedTact()->getBegin();
}

BOOL NotesEditor::emptyEnding() {
	for (int i = 0; i < this->composition->getSize(); i++) {
		Track* track = this->composition->getTrack(i);
		if (!track->getBack()->isEmpty()) {
			return FALSE;
		}
	}
	return TRUE;
}

void NotesEditor::deleteEnding() {
	this->composition->popTactInfo();
	for (int i = 0; i < this->composition->getSize(); i++) {
		Track* track = this->composition->getTrack(i);
		track->popTact();
	}
}

Tact * NotesEditor::getSelectedTact() {
	return this->selectedTact->getTact();
}

Event * NotesEditor::getSelectedEvent() {
	return this->selectedEvent->getEvent();
}

TrackEditor * NotesEditor::findTrackEditorByTrack(Track * track) {
	for (int i = 0; i < this->trackEditors.size(); i++) {
		if (this->trackEditors.at(i)->getTrack() == track) {
			return this->trackEditors.at(i);
		}
	}
	return NULL;
}

vector<TrackEditor*>::iterator NotesEditor::findTrackEditorIteratorByTrack(Track * track) {
	vector<TrackEditor*>::iterator current = this->trackEditors.begin();
	vector<TrackEditor*>::iterator end = this->trackEditors.end();
	while (current != end) {
		if ((*current)->getTrack() == track) {
			break;
		}
	}
	return current;
}

void NotesEditor::clearComposition() {
	if (this->composition != NULL) {
		delete this->composition;
		this->composition = NULL;
	}
	if (this->selectedEvent != NULL) {
		delete this->selectedEvent;
		this->selectedEvent = NULL;
	}
	if (this->selectedTact != NULL) {
		delete this->selectedTact;
		this->selectedTact = NULL;
	}
	for (TrackEditor* trackEditor : this->trackEditors) {
		delete trackEditor;
	}
	this->trackEditors.clear();

}

UCHAR NotesEditor::FindMinValueNotInSet(UCHAR beginValue, set<UCHAR>* set) {
	while (set->find(beginValue) != set->end()) {
		beginValue++;
	}
	return beginValue;
}

vector<EventInfo> NotesEditor::GetEventsForTactDuration(TactDuration * tactDuration) {
	EventInfo eventInfo;
	vector<EventInfo> result;
	USHORT tactBeatCount = Tact::getTactAbsoluteBeatCount(tactDuration);
	while (tactBeatCount != 0) {
		UCHAR eventBeatCount = Event::getAbsoluteBeatCount(&eventInfo);
		if (eventBeatCount > tactBeatCount) {
			eventInfo.beatType = (BeatType)(((UCHAR)eventInfo.beatType) / 2);
		} else {
			tactBeatCount -= eventBeatCount;
			result.push_back(eventInfo);
		}
	}
	return result;
}
