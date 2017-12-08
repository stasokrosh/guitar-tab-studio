#include "stdafx.h"
#include "Composition.h"

Composition::Composition(CompositionInfo compositionInfo, UCHAR velocity) {
	this->compositionInfo = compositionInfo;
	this->setVelocity(velocity);
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
	MidiTrack* selectedMidiTrack;
	MidiTrack** tracks = new MidiTrack*[this->getSize()];
	TrackIterator begin = this->getBegin();
	TrackIterator end = this->getEnd();
	UCHAR notPreferredChannelBeginValue = 0;
	int i = 0;
	while (begin != end) {
		UCHAR preferedChannel = (*begin)->getTrackInfo()->instrument->getPreferedChannel();
		if (preferedChannel == -1) {
			notPreferredChannelBeginValue = Composition::findMinValueNotInSet(notPreferredChannelBeginValue, channelSet);
			preferedChannel = notPreferredChannelBeginValue;
			notPreferredChannelBeginValue++;
		}
		tracks[i] = (*begin)->getMidiTrack(preferedChannel, midiDevice, selectedTact);
		if (*begin == selectedTrack) {
			selectedMidiTrack = tracks[i];
		}
		i++;
		begin++;
	}
	delete channelSet;
	return new MidiComposition(midiDevice, this->compositionInfo.tempo, tracks, this->getSize(), selectedMidiTrack);
}

TrackIterator Composition::addTrack(TrackInfo trackInfo, UCHAR velocity) {
	return Sequence<Track>::addElement(new Track(trackInfo, velocity, this));
}

void Composition::insertTrack(TrackIterator iterator, TrackInfo trackInfo, UCHAR velocity) {
	Sequence<Track>::insertElement(iterator, new Track(trackInfo, velocity, this));
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

void Composition::setVelocity(UCHAR velocity) {
	this->velocity = velocity;
	TrackIterator begin = this->getBegin();
	TrackIterator end = this->getEnd();
	while (begin != end) {
		(*begin)->setVelocity((*begin)->getVelocity());
		begin++;
	}
}

UCHAR Composition::getVelocity() {
	return UCHAR();
}

set<UCHAR>* Composition::validateChannelRelation() {
	TrackIterator begin = this->getBegin();
	TrackIterator end = this->getEnd();
	set<UCHAR>* channelSet = new set<UCHAR>();
	while (begin != end) {
		UCHAR preferedChannel = (*begin)->getTrackInfo()->instrument->getPreferedChannel();
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