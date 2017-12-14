#pragma once
#include "Common.h"
#include "Tact.h"
#include "Composition.h"
#include "TactIterator.h"
#include "TactFactory.h"

#include "MidiTrack.h"
#include "MidiDevice.h"

#include "NotesEditor.h"

using namespace std;

class Track {
public:
	Track(TrackInfo trackInfo, Instrument* instrument, TactFactory* tactFactory);
	~Track();
	BOOL isValid();
	void setComposition(Composition* composition);
	Composition* getComposition();
	MidiTrack* getMidiTrack(NotesEditor* notesEditor, UCHAR channel, MidiDevice* midiDevice, TactInfo* tact, Callback* changeNoteCallback);
	UCHAR getVelocity();
	wstring getName();
	Instrument* getInstrument();
	TrackInfo* getTrackInfo();
	void setName(wstring name);
	void updateVelocity();
	void setVelocity(UCHAR velocity);
	TactIterator* findIteratorByTactInfo(TactInfo* tactInfo);

	virtual Tact* getFront() = 0;
	virtual Tact* getBack() = 0;
	virtual TactIterator* pushTact(TactInfo* tactInfo) = 0;
	virtual void popTact() = 0;
	virtual UCHAR getSize() = 0;
	virtual TactIterator* getBegin() = 0;
	virtual TactIterator* getEnd() = 0;
	virtual TactIteratorTemplate<T>* getTactIteratorByPosition(USHORT position) = 0;
protected:
	Composition* composition;
	TrackInfo trackInfo;
	UCHAR effectiveVelocity;
	TactFactory* tactFactory;
	Instrument* instrument;

	void moveSelectorBack(TactIterator* current, TactIterator* begin);
	void createNewReprise(TactIterator* current, vector<pair<Tact*, UCHAR>>* repriseStack);
};
