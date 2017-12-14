#include "stdafx.h"
#include "GuitarTrackEditor.h"


GuitarTrackEditor::GuitarTrackEditor(TrackTemplate<GuitarTact>* guitarTrack, Guitar* guitar, NotesEditor* NotesEditor) : TrackEditor(guitarTrack, NotesEditor) {
	this->guitar = guitar;
	this->guitarTrack = guitarTrack;
	this->stringSelected = FALSE;
	this->trackViewComponent = NULL;
}


GuitarTrackEditor::~GuitarTrackEditor() {
	delete this->guitar;
	if (this->trackViewComponent != NULL) {
		delete this->trackViewComponent;
	}
}

void GuitarTrackEditor::moveUp() {
	if (!this->getSelectedEvent()->isPause()) {
		this->stringSelected = TRUE;
		if (this->selectedString != 0) {
			this->selectedString--;
		}
	}
}

void GuitarTrackEditor::moveDown() {
	if (!this->getSelectedEvent()->isPause()) {
		this->stringSelected = TRUE;
		if (this->selectedString != this->guitar->getStringCount() - 1) {
			this->selectedString++;
		}
	}
}

void GuitarTrackEditor::selectString(UCHAR num) {
	if (!this->getSelectedEvent()->isPause()) {
		this->selectedString = num;
		this->stringSelected = TRUE;
	}
}

void GuitarTrackEditor::deselectString() {
	this->stringSelected = FALSE;
}

TrackViewComponent * GuitarTrackEditor::getTrackViewComponent(ViewInfo * viewInfo) {
	if (this->trackViewComponent != NULL) {
		delete this->trackViewComponent;
	}
	this->trackViewComponent = new TrackViewComponent(viewInfo);
	TactIteratorTemplate<GuitarTact>* iterator = this->guitarTrack->getBegin();
	TactIteratorTemplate<GuitarTact>* end = this->guitarTrack->getEnd();
	vector<ViewComponent*> tacts;
	ViewComponent* selectedComponent;
	USHORT i = 0;
	while (!iterator->equal(end)) {
		GuitarTact* guitarTact = iterator->getTemplateTact();
		GuitarTactViewComponent* tactViewComponent = guitarTact->getViewComponent(viewInfo, i + 1);
		if (i == this->guitarTrack->getSize() - 1) {
			tactViewComponent->setLast(TRUE);
		}
		vector<GuitarEventViewComponent*> events;
		EventIteratorTemplate<GuitarEvent>* eventIterator = guitarTact->getBegin();
		EventIteratorTemplate<GuitarEvent>* endIterator = guitarTact->getEnd();
		while (!eventIterator->equal(endIterator)) {
			GuitarEvent* event = eventIterator->getTemplateEvent();
			GuitarEventViewComponent* eventViewComponent = event->getViewComponent(viewInfo, this->notesEditor, this);
			if (event == this->getSelectedEvent()) {
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
			HeaderViewComponent* header = new HeaderViewComponent(viewInfo, 
				this->notesEditor->getComposition()->getCompositionInfo(), this->guitarTrack->getTrackInfo(), this->guitar);
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
	TactIteratorTemplate<GuitarTact>* iterator = this->guitarTrack->getBegin();
	TactIteratorTemplate<GuitarTact>* end = this->guitarTrack->getEnd();
	while (!iterator->equal(end)) {
		GuitarTact* tact = iterator->getTemplateTact();
		if (tact == this->notesEditor->getSelectedTact()) {
			WriteLine(stream, to_wstring(TRUE));
		} else {
			WriteLine(stream, to_wstring(FALSE));
		}
		UCHAR size = tact->getSize();
		WriteLine(stream,to_wstring(size));
		EventIteratorTemplate<GuitarEvent>* eventIterator = tact->getBegin();
		EventIteratorTemplate<GuitarEvent>* eventEndIterator = tact->getEnd();
		while (!eventIterator->equal(eventEndIterator)) {
			GuitarEvent* guitarEvent = eventIterator->getTemplateEvent();
			if (guitarEvent == this->notesEditor->getSelectedEvent()) {
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

BOOL GuitarTrackEditor::Load(wifstream * stream, vector<TactInfo*>* tacts, TactIterator ** selectedTact,
	EventIterator ** selectedEvent) {
	if (!ReadGuitar(stream, this->guitar)) {
		return FALSE;
	}
	wstring text;
	ReadLine(stream, &text);
	this->stringSelected = (BOOL)stoi(text);
	ReadLine(stream, &text);
	this->selectedString = (UCHAR)stoi(text);
	for (USHORT i = 0; i < tacts->size(); i++) {
		ReadLine(stream, &text);
		TactIterator* iterator = this->getTrack()->pushTact(tacts->at(i));
		Tact* tact = iterator->getTact();
		BOOL selected = (BOOL)stoi(text);
		if (selected) {
			*selectedTact = iterator;
		} else {
			delete iterator;
		}
		ReadLine(stream, &text);
		UCHAR eventCount = (UCHAR)stoi(text);
		for (UCHAR j = 0; j < eventCount; j++) {
			ReadLine(stream, &text);
			BOOL selected = (BOOL)stoi(text);
			EventInfo eventInfo;
			if (!ReadEventInfo(stream, &eventInfo)) {
				return FALSE;
			}
			EventIterator* iterator = tact->pushEvent(eventInfo);
			Event* event = iterator->getEvent();
			if (selected) {
				*selectedEvent = iterator;
			} else {
				delete iterator;
			}
			GuitarEvent* guitarEvent = reinterpret_cast<GuitarEvent*>(event);
			if (!ReadGuitarEvent(stream, guitarEvent)) {
				return false;
			}
		}
	}
	return TRUE;
}

GuitarEvent * GuitarTrackEditor::getSelectedGuitarEvent() {
	return reinterpret_cast<GuitarEvent*>(this->getSelectedEvent());
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

