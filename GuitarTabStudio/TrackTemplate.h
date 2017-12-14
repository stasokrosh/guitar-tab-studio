#pragma once
#include "Track.h"
#include "TactIteratorTemplate.h"

template<class T>
class TrackTemplate : public Track {
public:
	TrackTemplate(TrackInfo trackInfo, Instrument* instrument, TactFactory* tactFactory);
	~TrackTemplate();
	virtual Tact* getFront();
	virtual Tact* getBack();
	virtual T* getTemplateFront();
	virtual T* getTemplateBack();
	virtual TactIteratorTemplate<T>* pushTact(TactInfo* tactInfo);
	virtual void popTact();
	virtual UCHAR getSize();
	virtual TactIteratorTemplate<T>* getBegin();
	virtual TactIteratorTemplate<T>* getEnd();
	virtual TactIteratorTemplate<T>* getTactIteratorByPosition(USHORT position);
private:
	vector<T*> tacts;
};

