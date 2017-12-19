#include "stdafx.h"
#include "NotesEditor.h"


NotesEditor::NotesEditor(FactoryOfTrackEditorFactory* factoryOfTEFactory, Callback* updateCallback) {
	this->factoryOfTEFactory = factoryOfTEFactory;
	this->selectedTrackEditor = NULL;
	this->fileName = L"";
	this->selectedEvent = new SelectedEvent(updateCallback);
	this->updateCallback = updateCallback;
	this->composition = NULL;
}

void NotesEditor::createComposition(CompositionInfo compositionInfo) {
	if (this->composition != NULL) {
		delete this->composition;
	}
	this->composition = new Composition(compositionInfo);
}

BOOL NotesEditor::loadComposition(wstring name) {
	wifstream stream;
	Composition* oldComposition = this->composition;
	vector<TrackEditor*> oldtrackEditors = this->trackEditors;
	EventIterator* oldEventIterator = this->selectedEvent->getIterator();
	TrackEditor* oldSelectedEditor = this->selectedTrackEditor;
	this->trackEditors.erase(this->trackEditors.begin(), this->trackEditors.end());
	try {
		stream.open(name);
		CompositionInfo compositionInfo;
		if (!ReadCompositionInfo(&stream, &compositionInfo)) {
			this->trackEditors = oldtrackEditors;
			return FALSE;
		}
		this->composition = new Composition(compositionInfo);
		wstring text;
		ReadLine(&stream, &text);
		SHORT tactCount = stoi(text);
		vector<TactInfo*> tacts;
		for (SHORT i = 0; i < tactCount; i++) {
			TactInfo* tactInfo = new TactInfo(this->composition->getTactDuration());
			if (!ReadTactInfo(&stream, tactInfo)) {
				this->trackEditors = oldtrackEditors;
				this->composition = oldComposition;
				return FALSE;
			}
			this->composition->pushTactInfo(tactInfo);
			tacts.push_back(tactInfo);
		}
		ReadLine(&stream, &text);
		SHORT trackCount = stoi(text);
		for (SHORT i = 0; i < trackCount; i++) {
			ReadLine(&stream, &text);
			BOOL selected = (BOOL)stoi(text);
			TrackInfo trackInfo;
			if (!ReadTrackInfo(&stream, &trackInfo)) {
				this->trackEditors = oldtrackEditors;
				this->composition = oldComposition;
				this->selectedEvent->setIterator(oldEventIterator);
				this->selectedTrackEditor = oldSelectedEditor;
				return FALSE;
			}
			wstring name;
			Instruments type;
			if (!ReadInstrumentInfo(&stream, &name, &type)) {
				this->trackEditors = oldtrackEditors;
				this->composition = oldComposition;
				this->selectedEvent->setIterator(oldEventIterator);
				this->selectedTrackEditor = oldSelectedEditor;
				return FALSE;
			}
			TrackEditorFactory* factory = this->factoryOfTEFactory->getTrackEditorFactory(type);
			TrackEditor* trackEditor = factory->createTrackEditor(name, trackInfo, this->updateCallback);
			if (trackEditor == NULL) {
				this->trackEditors = oldtrackEditors;
				this->composition = oldComposition;
				this->selectedEvent->setIterator(oldEventIterator);
				this->selectedTrackEditor = oldSelectedEditor;
				return FALSE;
			}
			this->trackEditors.push_back(trackEditor);
			trackEditor->setSelectedEvent(this->selectedEvent);
			if (selected) {
				this->selectedTrackEditor = trackEditor;
			}
			if (!trackEditor->Load(&stream, &tacts)) {
				this->trackEditors = oldtrackEditors;
				this->composition = oldComposition;
				this->selectedEvent->setIterator(oldEventIterator);
				this->selectedTrackEditor = oldSelectedEditor;
				return FALSE;
			}
			composition->addTrack(trackEditor->getTrack());
		}
		stream.close();
		this->fileName = name;
		this->updateCallback->call();
		return TRUE;
	} catch (exception e) {
		puts(e.what());
		getchar();
		if (stream.is_open()) {
			stream.close();
		}
		return FALSE;
	}
}

void NotesEditor::saveComposition(wstring name) {
	wofstream stream(name);
	WriteCompositionInfo(&stream, this->composition->getCompositionInfo());
	SHORT tactInfoCount = this->composition->getTactInfoCount();
	WriteLine(&stream, to_wstring(tactInfoCount));
	for (SHORT i = 0; i < tactInfoCount; i++) {
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
	this->fileName = name;
	stream.close();
	this->updateCallback->call();
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
			this->updateCallback->call();
			return TRUE;
		}
	}
}

NotesEditor::~NotesEditor() {
	delete this->selectedEvent;
	this->clearComposition();
	delete this->updateCallback;
}

MidiComposition * NotesEditor::createMidiComposition(MidiDevice * midiDevice) {
	if (!(this->composition->isValid())) {
		return NULL;
	}
	TactIterator* selectedTact = this->selectedTrackEditor->getTactByEvent(this->selectedEvent->getIterator());
	TactInfo* selectedTactInfo = selectedTact->getTact()->getTactInfo();
	set<UCHAR>* channelSet = this->validateChannelRelation();
	if (!channelSet) {
		return NULL;
	}
	MidiTrack** tracks = new MidiTrack*[this->composition->getSize()];
	UCHAR notPreferredChannelBeginValue = 1;
	for (UCHAR i = 0; i < this->trackEditors.size(); i++) {
		TrackEditor* trackEditor = this->trackEditors.at(i);
		CHAR preferedChannel = trackEditor->getTrack()->getInstrument()->getPreferedChannel();
		if (preferedChannel == 0) {
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

void NotesEditor::deleteTrack(Track * track) {
	vector<TrackEditor*>::iterator iterator = this->findTrackEditorIteratorByTrack(track);
	if (iterator != this->trackEditors.end()) {
		this->trackEditors.erase(iterator, iterator);
	}
	this->selectTrack(this->composition->getTrack(0));
	this->updateCallback->call();
}

void NotesEditor::selectTrack(Track * track) {
	if (this->getSelectedEvent()->isEmpty()) {
		this->setEventPause(TRUE);
	}
	TrackEditor* trackEditor = this->findTrackEditorByTrack(track);
	if (trackEditor != NULL) {
		this->selectTrackEditor(trackEditor);
	}
	this->updateCallback->call();
}


void NotesEditor::setEventPause(BOOL pause) {
	this->getSelectedEvent()->setPause(pause);
	this->updateCallback->call();
}

void NotesEditor::setBeatType(BeatType beatType) {
	this->eventInfo.beatType = beatType;
	Event* event = this->getSelectedEvent();
	event->setBeatType(beatType);
	this->updateCallback->call();
}

void NotesEditor::setBeatTypeEx(BeatTypeEx beatTypeEx) {
	this->eventInfo.beatTypeEx = beatTypeEx;
	Event* event = this->getSelectedEvent();
	event->setBeatTypeEx(beatTypeEx);
	this->updateCallback->call();
}

void NotesEditor::setDotCount(UCHAR dotCount) {
	this->eventInfo.dotCount = dotCount;
	Event* event = this->getSelectedEvent();
	event->setDotCount(dotCount);
	this->updateCallback->call();
}

void NotesEditor::setRepriseBegin(BOOL begin, TactInfo * tactInfo) {
	tactInfo->repriseBegin = begin;
	this->updateCallback->call();
}

void NotesEditor::setRepriseEnd(UCHAR repriseCount, TactInfo * tactInfo) {
	tactInfo->repriseEnd = repriseCount;
	this->updateCallback->call();
}

void NotesEditor::setCompositionInfo(CompositionInfo * compositionInfo) {
	this->composition->setName(compositionInfo->name);
	this->composition->setAuthor(compositionInfo->author);
	this->composition->setTactDuration(compositionInfo->tactDuration);
	this->composition->setTempo(compositionInfo->tempo);
	this->updateCallback->call();
}

Track * NotesEditor::getSelectedTrack() {
	return this->selectedTrackEditor->getTrack();
}

Composition * NotesEditor::getComposition() {
	return this->composition;
}

TrackEditor * NotesEditor::getSelectedTrackEditor() {
	return this->selectedTrackEditor;
}

FactoryOfTrackEditorFactory * NotesEditor::getFactory() {
	return this->factoryOfTEFactory;
}

void NotesEditor::moveForward() {
	EventIterator* selectedEventIterator = this->selectedEvent->getIterator();
	if (this->getSelectedEvent()->isEmpty()) {
		TactIterator* tactIterator = this->getSelectedTactIterator();
		Tact* selectedTact = tactIterator->getTact();
		if (selectedTact->getSize() == 1) {
			this->setEventPause(TRUE);
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
		if (selectedEventIterator->isLast()) {
			selectedEventIterator->insertEvent(this->eventInfo);
			selectedEventIterator->moveForward();
			this->getSelectedEvent()->setEmpty();
		} else {
			selectedEventIterator->moveForward();
		}
	}
	this->selectedTrackEditor->moveForward();
	this->updateCallback->call();
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
	this->selectedTrackEditor->moveBackwards();
	this->updateCallback->call();
}

TrackViewComponent* NotesEditor::getTrackViewComponent(ViewInfo* viewInfo) {
	return this->selectedTrackEditor == NULL ? NULL : selectedTrackEditor->getTrackViewComponent(viewInfo,
		this->composition->getCompositionInfo());
}

Event* NotesEditor::getSelectedEvent() {
	EventIterator* iterator = this->selectedEvent->getIterator();
	return iterator == NULL ? NULL : iterator->getEvent();
}

TactInfo * NotesEditor::getSelectedTact() {
	if (this->selectedTrackEditor == NULL) {
		return NULL;
	} else {
		TactIterator* iterator = this->selectedTrackEditor->getTactByEvent(this->selectedEvent->getIterator());
		TactInfo* tactInfo = iterator->getTact()->getTactInfo();
		delete iterator;
		return tactInfo;
	}
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
		i++;
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
	} else {
		TactIterator* iterator = trackEditor->getTrack()->getBegin();
		this->selectedEvent->setIterator(iterator->getTact()->getBegin());
		delete iterator;
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
	eventInfo.beatType = WHOLE;
	vector<EventInfo> result;
	SHORT tactBeatCount = Tact::getTactAbsoluteBeatCount(tactDuration);
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
