#pragma once
#include "Common.h"

#include "Tact.h"
#include "TactIterator.h"
#include "TactFactory.h"
#include "Instrument.h"
#include <string>
#include <vector>

using namespace std;


class Track {
public:
	Track(TrackInfo trackInfo, Instrument* instrument, TactFactory* tactFactory);
	virtual ~Track();
	BOOL isValid();
	UCHAR getVelocity();
	wstring getName();
	Instrument* getInstrument();
	TrackInfo* getTrackInfo();
	void setName(wstring name);
	void setVelocity(UCHAR velocity);

	virtual Tact* getFront() = 0;
	virtual Tact* getBack() = 0;
	virtual TactIterator* pushTact(TactInfo* tactInfo) = 0;
	virtual void popTact() = 0;
	virtual UCHAR getSize() = 0;
	virtual TactIterator* getBegin() = 0;
	virtual TactIterator* getEnd() = 0;
protected:
	TrackInfo trackInfo;
	UCHAR* compositionVelocity;
	TactFactory* tactFactory;
	Instrument* instrument;
};
