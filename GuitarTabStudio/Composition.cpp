#include "stdafx.h"
#include "Composition.h"

Composition::Composition(CompositionInfo compositionInfo, UCHAR tempo, TactDuration tactDuration) {
	this->compositionInfo = compositionInfo;
	this->tempo = tempo;
	this->tactDuration = tactDuration;
}


Composition::~Composition() {}


MidiComposition * Composition::createMidiComposition(MidiDevice * midiDevice, Track* selectedTrack, TactInfo* selectedTact) {
	if (!this->isValid()) {
		return FALSE;
	}
	set<UCHAR>* channelSet = this->validateChannelRelation();
	if (!channelSet) {
		return NULL;
	}
	vector<MidiTrack*>* tracks = new vector<MidiTrack*>();
	TrackIterator begin = this->getBegin();
	TrackIterator end = this->getEnd();
	UCHAR notPreferredChannelBeginValue = 0;
	while (begin != end) {
		UCHAR preferedChannel = (*begin)->instrument->getPreferedChannel();
		if (preferedChannel == -1) {
			notPreferredChannelBeginValue = Composition::findMinValueNotInSet(notPreferredChannelBeginValue, channelSet);
			preferedChannel = notPreferredChannelBeginValue;
			notPreferredChannelBeginValue++;
		}
		tracks->push_back((*begin)->getMidiTrack(preferedChannel, midiDevice, selectedTact));
		begin++;
	}
	delete channelSet;
	return new MidiComposition(midiDevice, this->tempo, tracks);
}

TrackIterator Composition::addElement(Track * pElement) {
	pElement->composition = this;
	return Sequence<Track>::addElement(pElement);
}

void Composition::insertElement(TrackIterator iterator, Track * pElement) {
	pElement->composition = this;
	Sequence<Track>::insertElement(iterator, pElement);
}

BOOL Composition::isValid() {
	TrackIterator begin = this->getBegin();
	TrackIterator end = this->getEnd();
	while (begin != end) {
		if (!(*begin)->isValid()) {
			return FALSE;
		}
		begin++;
	}
	return TRUE;
}

set<UCHAR>* Composition::validateChannelRelation() {
	TrackIterator begin = this->getBegin();
	TrackIterator end = this->getEnd();
	set<UCHAR>* channelSet = new set<UCHAR>();
	while (begin != end) {
		UCHAR preferedChannel = (*begin)->instrument->getPreferedChannel();
		if (preferedChannel != -1) {
			std::pair<set<UCHAR>::iterator, bool> pair = channelSet->insert(preferedChannel);
			if (!pair.second) {
				delete channelSet;
				return NULL;
			}
		}
		begin++;
	}
	return channelSet;
}

UCHAR Composition::findMinValueNotInSet(UCHAR beginValue, set<UCHAR>* set) {
	while (set->find(beginValue) != set->end()) {
		beginValue++;
	}
	return beginValue;
}