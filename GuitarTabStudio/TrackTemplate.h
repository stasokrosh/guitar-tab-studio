#pragma once
#include "Track.h"
#include "TactIteratorTemplate.h"
#include <vector>

using namespace std;

template<class T>
class TrackTemplate : public Track {
public:
	TrackTemplate(TrackInfo trackInfo, Instrument* instrument, TactFactory* tactFactory);
	~TrackTemplate();
	virtual Tact* getFront();
	virtual Tact* getBack();
	virtual T* getTemplateFront();
	virtual T* getTemplateBack();
	virtual TactIterator* pushTact(TactInfo* tactInfo);
	virtual void popTact();
	virtual UCHAR getSize();
	virtual TactIterator* getBegin();
	virtual TactIterator* getEnd();
	virtual TactIteratorTemplate<T>* getTemplateBegin();
	virtual TactIteratorTemplate<T>* getTemplateEnd();
private:
	vector<T*> tacts;
};

