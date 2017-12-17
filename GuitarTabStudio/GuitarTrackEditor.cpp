#include "stdafx.h"
#include "GuitarTrackEditor.h"


GuitarTrackEditor::GuitarTrackEditor(TrackTemplate<GuitarTact>* guitarTrack, Guitar* guitar, Callback* updateCallback) : 
	TrackEditor(guitarTrack, updateCallback) {
	this->guitar = guitar;
	this->guitarTrack = guitarTrack;
	this->stringSelected = FALSE;
	this->trackViewComponent = NULL;
	this->selectedString = 0;
}


GuitarTrackEditor::~GuitarTrackEditor() {
	delete this->guitar;
	if (this->trackViewComponent != NULL) {
		delete this->trackViewComponent;
	}
}

void GuitarTrackEditor::moveUp() {
	if (!this->getSelectedGuitarEvent()->isPause()) {
		this->stringSelected = TRUE;
		if (this->selectedString != 0) {
			this->selectedString--;
		}
	}
}

void GuitarTrackEditor::moveDown() {
	if (!this->getSelectedGuitarEvent()->isPause()) {
		this->stringSelected = TRUE;
		if (this->selectedString != this->guitar->getStringCount() - 1) {
			this->selectedString++;
		}
	}
}

void GuitarTrackEditor::selectString(UCHAR num) {
	if (!this->getSelectedGuitarEvent()->isPause()) {
		this->selectedString = num;
		this->stringSelected = TRUE;
	}
}

void GuitarTrackEditor::deselectString() {
	this->stringSelected = FALSE;
}

TrackViewComponent * GuitarTrackEditor::getTrackViewComponent(ViewInfo * viewInfo, CompositionInfo* compositionInfo) {
	if (this->trackViewComponent != NULL) {
		delete this->trackViewComponent;
	}
	this->trackViewComponent = new TrackViewComponent(viewInfo);
	TactIteratorTemplate<GuitarTact>* iterator = this->guitarTrack->getTemplateBegin();
	TactIteratorTemplate<GuitarTact>* end = this->guitarTrack->getTemplateEnd();
	vector<ViewComponent*> tacts;
	ViewComponent* selectedComponent = NULL;
	USHORT i = 0;
	while (!iterator->equal(end)) {
		GuitarTact* guitarTact = iterator->getTemplateTact();
		GuitarTactViewComponent* tactViewComponent = this->getTactViewComponent(viewInfo, i + 1, guitarTact);
		vector<GuitarEventViewComponent*> events;
		EventIteratorTemplate<GuitarEvent>* eventIterator = guitarTact->getTemplateBegin();
		EventIteratorTemplate<GuitarEvent>* endIterator = guitarTact->getTemplateEnd();
		while (!eventIterator->equal(endIterator)) {
			GuitarEvent* event = eventIterator->getTemplateEvent();
			GuitarEventViewComponent* eventViewComponent = this->getEventViewComponent(viewInfo, eventIterator);
			if (event == this->selectedEvent->getIterator()->getEvent()) {
				selectedComponent = eventViewComponent;
			}
			events.push_back(eventViewComponent);
		}
		tactViewComponent->addEvents(events);
		tacts.push_back(tactViewComponent);
		i++;
		iterator->moveForward();
	}
	this->trackViewComponent->setSelectedViewComponent(selectedComponent);
	vector<PageViewComponent*> pages;
	i = 0;
	while (tacts.size() != 0) {
		PageViewComponent* page;
		if (i == 0) {
			HeaderViewComponent* header = new HeaderViewComponent(viewInfo, compositionInfo, 
				this->guitarTrack->getTrackInfo(), this->guitar);
			page = new HeaderPageViewComponent(viewInfo, header);
		} else {
			page = new SimplePageViewComponent(viewInfo, i);
		}
		page->getTactContainer()->addTacts(&tacts);
		pages.push_back(page);
	}
	this->trackViewComponent->addPages(pages);
	return this->trackViewComponent;
}

void GuitarTrackEditor::setCapo(UCHAR capo) {
	this->guitar->setCapo(capo);
}

void GuitarTrackEditor::Write(wofstream * stream) {
	WriteGuitar(stream, this->guitar);
	WriteLine(stream, to_wstring(this->stringSelected));
	WriteLine(stream, to_wstring(this->selectedString));
	TactIteratorTemplate<GuitarTact>* iterator = this->guitarTrack->getTemplateBegin();
	TactIteratorTemplate<GuitarTact>* end = this->guitarTrack->getTemplateEnd();
	while (!iterator->equal(end)) {
		GuitarTact* tact = iterator->getTemplateTact();
		UCHAR size = tact->getSize();
		WriteLine(stream,to_wstring(size));
		EventIteratorTemplate<GuitarEvent>* eventIterator = tact->getTemplateBegin();
		EventIteratorTemplate<GuitarEvent>* eventEndIterator = tact->getTemplateEnd();
		while (!eventIterator->equal(eventEndIterator)) {
			GuitarEvent* guitarEvent = eventIterator->getTemplateEvent();
			if (guitarEvent == this->selectedEvent->getIterator()->getEvent()) {
				WriteLine(stream, to_wstring(TRUE));
			} else {
				WriteLine(stream, to_wstring(FALSE));
			}
			WriteEventInfo(stream, guitarEvent->getEventInfo());
			WriteGuitarEvent(stream, guitarEvent);
			eventIterator->moveForward();
		}
		delete eventIterator;
		delete eventEndIterator;
		iterator->moveForward();
	}
	delete iterator;
	delete end;
}

BOOL GuitarTrackEditor::Load(wifstream * stream, vector<TactInfo*>* tacts) {
	if (!ReadGuitar(stream, this->guitar)) {
		return FALSE;
	}
	wstring text;
	ReadLine(stream, &text);
	this->stringSelected = (BOOL)stoi(text);
	ReadLine(stream, &text);
	this->selectedString = (UCHAR)stoi(text);
	for (USHORT i = 0; i < tacts->size(); i++) {
		TactIterator* iterator = this->getTrack()->pushTact(tacts->at(i));
		Tact* tact = iterator->getTact();
		ReadLine(stream, &text);
		UCHAR eventCount = (UCHAR)stoi(text);
		for (UCHAR j = 0; j < eventCount; j++) {
			ReadLine(stream, &text);
			BOOL selected = (BOOL)stoi(text);
			EventInfo eventInfo;
			if (!ReadEventInfo(stream, &eventInfo)) {
				return FALSE;
			}
			EventIterator* eventIterator = tact->pushEvent(eventInfo);
			Event* event = eventIterator->getEvent();
			if (selected) {
				this->selectedEvent->setIterator(eventIterator);
			} else {
				delete eventIterator;
			}
			GuitarEvent* guitarEvent = reinterpret_cast<GuitarEvent*>(event);
			if (!ReadGuitarEvent(stream, guitarEvent)) {
				return false;
			}
		}
	}
	return TRUE;
}

void GuitarTrackEditor::preparePlaying() {
	this->stringSelected = FALSE;
}

MidiEvent* GuitarTrackEditor::getMidiEvent(Event* event, UCHAR channel, Callback* selectEventCallback) {
	GuitarEvent* guitarEvent = reinterpret_cast<GuitarEvent*>(event);
	if (guitarEvent->isPause()) {
		return new MidiEvent(guitarEvent->getAbsoluteBeatCount(), channel, selectEventCallback);
	} else {
		vector<UCHAR> notes;
		for (UCHAR i = 0; i < guitarEvent->getStringCount(); i++) {
			if (*(guitarEvent->getNote(i)) != -1) {
				notes.push_back(*(guitarEvent->getNote(i)));
			}
		}
		return new GuitarMidiEvent(guitarEvent->getAbsoluteBeatCount(), channel, notes, guitarEvent->getChordDirection(),
			&(this->track->getTrackInfo()->velocity), selectEventCallback);
	}
}

GuitarTactViewComponent* GuitarTrackEditor::getTactViewComponent(ViewInfo* viewInfo, USHORT num, GuitarTact* tact) {
	if (num == 1) {
		return new GuitarHeadTactViewComponent(viewInfo, this->guitar, tact->getTactInfo(), tact->isValid());
	} else {
		return new GuitarTactViewComponent(viewInfo, num, this->guitar->getStringCount(), tact->getTactInfo(), tact->isValid());
	}
}

GuitarEventViewComponent* GuitarTrackEditor::getEventViewComponent(ViewInfo* viewInfo,EventIteratorTemplate<GuitarEvent>* iterator) {
	Callback* clickCallback = new SelectedEvent::SelectEventCallback(this->selectedEvent, iterator);
	GuitarEvent* guitarEvent = iterator->getTemplateEvent();
	BOOL selected = guitarEvent == this->getSelectedGuitarEvent();
	CHAR stringSelected = this->stringSelected ? this->selectedString : -1;
	vector<Callback*> notesCallbacks;
	for (UCHAR i = 0; i < guitarEvent->getStringCount(); i++) {
		Callback* callback;
		if (guitarEvent->isPause()) {
			callback = NULL;
		} else {
			callback = new SelectStringCallback(clickCallback, i, this);
		}
	}
	return new GuitarEventViewComponent(viewInfo, clickCallback, notesCallbacks, guitarEvent, selected, stringSelected);
}

GuitarEvent * GuitarTrackEditor::getSelectedGuitarEvent() {
	return reinterpret_cast<GuitarEvent*>(this->selectedEvent->getIterator()->getEvent());
}

void GuitarTrackEditor::WriteGuitarEvent(wofstream * stream, GuitarEvent * guitarEvent) {
	WriteLine(stream, to_wstring(guitarEvent->getChordDirection()));
	wstring line;
	for (UCHAR i = 0; i < guitarEvent->getStringCount(); i++) {
		line += to_wstring(*(guitarEvent->getNote(i)));
		if (i != guitarEvent->getStringCount() - 1) {
			line += L" ";
		}
	}
	WriteLine(stream, line);
}

BOOL GuitarTrackEditor::ReadGuitarEvent(wifstream * stream, GuitarEvent * guitarEvent) {
	wstring text;
	ReadLine(stream, &text);
	ChordDirections chordDirection = (ChordDirections)stoi(text);
	guitarEvent->setChordDirection(chordDirection);
	vector<wstring> notes = ReadVector(stream);
	if (notes.size() != guitarEvent->getStringCount()) {
		return FALSE;
	}
	for (UCHAR i = 0; i < notes.size(); i++) {
		CHAR note = (CHAR)stoi(notes.at(i));
		*(guitarEvent->getNote(i)) = note;
	}
	return TRUE;
}

void GuitarTrackEditor::WriteGuitar(wofstream * stream, Guitar * guitar) {
	WriteLine(stream, to_wstring(guitar->getCapo()));
	for (UCHAR i = 0; i < guitar->getStringCount(); i++) {
		Note* note = guitar->getString(i);
		wstring text = to_wstring(note->frequency) + L" " + to_wstring(note->octave);
		WriteLine(stream, text);
	}
}

BOOL GuitarTrackEditor::ReadGuitar(wifstream * stream, Guitar * guitar) {
	wstring text;
	ReadLine(stream, &text);
	UCHAR capo = (UCHAR)stoi(text);
	for (UCHAR i = 0; i < guitar->getStringCount(); i++) {
		vector<wstring> noteVector = ReadVector(stream);
		if (noteVector.size() != 2) {
			return FALSE;
		}
		Note note;
		note.frequency = (Notes)stoi(noteVector.at(0));
		note.octave = (UCHAR)stoi(noteVector.at(1));
		(*guitar->getString(i)) = note;
	}
	return TRUE;
}

GuitarTrackEditor::SelectStringCallback::SelectStringCallback(Callback* selectEventCallback, UCHAR stringNum, 
	GuitarTrackEditor* trackEditor) {
	this->selectEventCallback = selectEventCallback;
	this->stringNum = stringNum;
	this->trackEditor = trackEditor;
}

GuitarTrackEditor::SelectStringCallback::~SelectStringCallback() {
}

void GuitarTrackEditor::SelectStringCallback::call() {
	this->trackEditor->selectString(this->stringNum);
	this->selectEventCallback->call();
}

