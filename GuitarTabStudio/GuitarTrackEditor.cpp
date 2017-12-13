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

GuitarEvent * GuitarTrackEditor::getSelectedGuitarEvent() {
	return reinterpret_cast<GuitarEvent*>(this->getSelectedEvent());
}

