#include "stdafx.h"
#include "NotesEditor.h"


NotesEditor::NotesEditor(FactoryOfTrackEditorFactory* factoryOfTEFactory, Callback* updateCallback) {
	this->factoryOfTEFactory = factoryOfTEFactory;
	this->selectedTrackEditor = NULL;
	this->fileName = L"";
	this->selectedEvent = new SelectedEvent(updateCallback);
	this->updateCallback = updateCallback;
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
			TrackEditor* trackEditor = factory->createTrackEditor(name, trackInfo, this->updateCallback);
			if (trackEditor == NULL) {
				return FALSE;
			}
			this->trackEditors.push_back(trackEditor);
			if (selected) {
				this->selectedTrackEditor = trackEditor;
			}
			if (!trackEditor->Load(&stream, &tacts)) {
				return FALSE;
			}
		}
		stream.close();
		return TRUE;
	} catch (exception e) {
		if (stream.is_open()) {
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
		TrackEditor* trackEditor = trackEditorFactory->createTrackEditor(instrumentName, trackInfo, this->updateCallback);
		if (trackEditor == NULL) {
			return FALSE;
		} else {
			trackEditor->setSelectedEvent(this->selectedEvent);
			this->composition->addTrack(trackEditor->getTrack());
			this->trackEditors.push_back(trackEditor);
			if (this->composition->getSize() == 1) {
				this->composition->pushTactInfo(new TactInfo(this->composition->getTactDuration()));
			}
			TrackEditor* trackEditor = this->trackEditors.back();
			vector<EventInfo> events = NotesEditor::GetEventsForTactDuration(this->composition->getTactDuration());
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
	delete this->selectedEvent;
}

MidiComposition * NotesEditor::createMidiComposition(MidiDevice * midiDevice) {
	if (!this->composition->isValid()) {
		return NULL;
	}
	TactIterator* selectedTact = this->selectedTrackEditor->getTactByEvent(this->selectedEvent->getIterator());
	TactInfo* selectedTactInfo = selectedTact->getTact()->getTactInfo();
	set<UCHAR>* channelSet = this->validateChannelRelation();
	if (!channelSet) {
		return NULL;
	}
	MidiTrack** tracks = new MidiTrack*[this->composition->getSize()];
	UCHAR notPreferredChannelBeginValue = 0;
	for (UCHAR i = 0; i < this->trackEditors.size(); i++) {
		TrackEditor* trackEditor = this->trackEditors.at(i);
		UCHAR preferedChannel = trackEditor->getTrack()->getInstrument()->getPreferedChannel();
		if (preferedChannel == -1) {
			notPreferredChannelBeginValue = NotesEditor::FindMinValueNotInSet(notPreferredChannelBeginValue, channelSet);
			preferedChannel = notPreferredChannelBeginValue;
			notPreferredChannelBeginValue++;
		}
		tracks[i] = trackEditor->getMidiTrack(preferedChannel, midiDevice, selectedTactInfo, 
			trackEditor == this->selectedTrackEditor);
		i++;
	}
	this->selectedTrackEditor->preparePlaying();
	return new MidiComposition(midiDevice, this->composition->getTempo(), tracks, this->composition->getSize());
}

vector<Track*> NotesEditor::getTracks() {
	vector<Track*> result;
	for (int i = 0; i < this->composition->getSize(); i++) {
		result.push_back(this->composition->getTrack(i));
	}
	return result;
}

EventInfo*  NotesEditor::getEventInfo() {
	return &(this->eventInfo);
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


void NotesEditor::setEventPause() {
	this->getSelectedEvent()->setPause(TRUE);
}

Track * NotesEditor::getSelectedTrack() {
	return this->selectedTrackEditor->getTrack();
}

void NotesEditor::moveForward() {
	EventIterator* selectedEventIterator = this->selectedEvent->getIterator();
	if (this->getSelectedEvent()->isEmpty()) {
		TactIterator* tactIterator = this->getSelectedTactIterator();
		Tact* selectedTact = tactIterator->getTact();
		if (selectedTact->getSize() == 1) {
			this->setEventPause();
		} else {
			selectedEventIterator->deleteEvent();
		}
		if (selectedEventIterator->isLast()) {
			this->moveNextTact(tactIterator);
		} else {
			selectedEventIterator->moveForward();
		}
		delete tactIterator;
	} else {
		if (selectedEventIterator) {
			selectedEventIterator->insertEvent(this->eventInfo);
			selectedEventIterator->moveForward();
			this->getSelectedEvent()->setEmpty();
		} else {
			selectedEventIterator->moveForward();
		}
	}
}

void NotesEditor::moveBackward() {
	EventIterator* selectedEventIterator = this->selectedEvent->getIterator();
	if (this->getSelectedEvent()->isEmpty()) {
		TactIterator* tactIterator = this->getSelectedTactIterator();
		Tact* selectedTact = tactIterator->getTact();
		if (selectedTact->getSize() == 1) {
			this->getSelectedEvent()->setPause(TRUE);
		} else {
			selectedEventIterator->deleteEvent();
		}
		if (selectedEventIterator->isFirst()) {
			this->movePrevTact(tactIterator);
		}
		delete tactIterator;
	} else {
		if (selectedEventIterator->isFirst()) {
			TactIterator* tactIterator = this->getSelectedTactIterator();
			this->movePrevTact(tactIterator);
			delete tactIterator;
		} else {
			selectedEventIterator->moveBackwards();
		}
	}
}

TrackViewComponent* NotesEditor::getTrackViewComponent(ViewInfo* viewInfo) {
	return this->selectedTrackEditor == NULL ? NULL : selectedTrackEditor->getTrackViewComponent(viewInfo,
		this->composition->getCompositionInfo());
}

Event* NotesEditor::getSelectedEvent() {
	EventIterator* iterator = this->selectedEvent->getIterator();
	return iterator == NULL ? NULL : iterator->getEvent();
}

TactIterator* NotesEditor::getSelectedTactIterator() {
	return this->selectedTrackEditor->getTactByEvent(this->selectedEvent->getIterator());
}

void NotesEditor::addEmptyTact(Track * track, vector<EventInfo> events, TactInfo* tactInfo) {
	Tact* tact = track->pushTact(tactInfo)->getTact();
	for (EventInfo eventInfo : events) {
		tact->pushEvent(eventInfo);
	}
}

void NotesEditor::moveNextTact(TactIterator* currentTact) {
	if (currentTact->isLast()) {
		TactInfo* tactInfo = new TactInfo(this->composition->getTactDuration());
		this->composition->pushTactInfo(tactInfo);
		vector<EventInfo> events = NotesEditor::GetEventsForTactDuration(this->composition->getTactDuration());
		for (int i = 0; i < this->composition->getSize(); i++) {
			this->addEmptyTact(this->composition->getTrack(i), events, tactInfo);
		}
	}
	currentTact->moveForward();
	this->selectedEvent->setIterator(currentTact->getTact()->getBegin());
}

void NotesEditor::movePrevTact(TactIterator* currentTact) {
	if (!currentTact->isFirst()) {
		if (currentTact->isLast()) {
			if (this->emptyEnding()) {
				this->deleteEnding();
			}
		}
		currentTact->moveBackwards();
		EventIterator* eventIterator = currentTact->getTact()->getEnd();
		eventIterator->moveBackwards();
		this->selectedEvent->setIterator(eventIterator);
	}
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
	EventIterator* iterator = this->selectedEvent->getIterator();
	if (iterator != NULL) {
		TactIterator* tactIterator = this->selectedTrackEditor->getTactByEvent(iterator);
		TactIterator* newTactIterator = trackEditor->getTactByTactInfo(tactIterator->getTact()->getTactInfo());
		this->selectedEvent->setIterator(newTactIterator->getTact()->getBegin());
		delete tactIterator;
		delete tactIterator;
	}
	this->selectedTrackEditor = trackEditor;	
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
