#include "stdafx.h"
#include "TrackTemplate.h"

template<class T>
TrackTemplate<T>::TrackTemplate(TrackInfo trackInfo, Instrument* instrument, TactFactory* tactFactory)
	: Track(trackInfo, instrument, tactFactory) {

}

template<class T>
TrackTemplate<T>::~TrackTemplate() {}

template<class T>
Tact * TrackTemplate<T>::getFront() {
	return this->tacts.front();
}

template<class T>
Tact * TrackTemplate<T>::getBack() {
	return this->tacts.back();
}

template<class T>
T * TrackTemplate<T>::getTemplateFront() {
	return this->tacts.front();
}

template<class T>
T * TrackTemplate<T>::getTemplateBack() {
	return this->tacts.back();
}

template<class T>
TactIterator* TrackTemplate<T>::pushTact(TactInfo * tactInfo) {
	this->tacts.push_back(this->tactFactory->createTact(tactInfo));
	return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.end()--, this->tactFactory);
}

template<class T>
void TrackTemplate<T>::popTact() {
	this->tacts.pop_back();
}

template<class T>
UCHAR TrackTemplate<T>::getSize() {
	return this->tacts.size();
}

template<class T>
TactIterator* TrackTemplate<T>::getBegin() {
	return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.begin(), this->tactFactory);
}

template<class T>
TactIterator* TrackTemplate<T>::getEnd() {
	return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.end(), this->tactFactory);
}

template <class T>
TactIteratorTemplate<T>* TrackTemplate<T>::getTemplateBegin() {
	return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.begin(), this->tactFactory);
}

template <class T>
TactIteratorTemplate<T>* TrackTemplate<T>::getTemplateEnd() {
	return new TactIteratorTemplate<T>(&(this->tacts), this->tacts.end(), this->tactFactory);
}


