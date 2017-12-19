#pragma once
#include "Track.h"
#include "TactIteratorTemplate.h"
#include <vector>

using namespace std;

template<class T>
class TrackTemplate : public Track {
public:
	TrackTemplate(TrackInfo trackInfo, Instrument* instrument, TactFactory* tactFactory) : 
		Track(trackInfo, instrument, tactFactory) {
	}
	virtual ~TrackTemplate() {
		this->tacts.clear();
	}
	virtual Tact* getFront() {
		return this->tacts.front();
	}
	virtual Tact* getBack() {
		return this->tacts.back();
	}
	virtual T* getTemplateFront() {
		return this->tacts.front();
	}
	virtual T* getTemplateBack() {
		return this->tacts.back();
	}
	virtual TactIterator* pushTact(TactInfo* tactInfo) {
		this->tacts.push_back(reinterpret_cast<T*>(this->tactFactory->createTact(tactInfo)));
		return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.size() - 1, this->tactFactory);
	}
	virtual void popTact() {
		this->tacts.pop_back();
	}
	virtual UCHAR getSize() {
		return this->tacts.size();
	}
	virtual TactIterator* getBegin() {
		return new TactIteratorTemplate<T>(&(this->tacts), 0, this->tactFactory);
	}
	virtual TactIterator* getEnd() {
		return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.size(), this->tactFactory);
	}
	virtual TactIteratorTemplate<T>* getTemplateBegin() {
		return new TactIteratorTemplate<T>(&(this->tacts), 0, this->tactFactory);
	}
	virtual TactIteratorTemplate<T>* getTemplateEnd() {
		return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.size(), this->tactFactory);
	}
private:
	vector<T*> tacts;
};

