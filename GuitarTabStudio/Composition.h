#pragma once
#include "Common.h"
#include <string>
#include <vector>
#include "Track.h"

using namespace std;

class Composition {
public:
	Composition(CompositionInfo compositionInfo);
	~Composition();
	BOOL isValid();
	UCHAR getSize();
	wstring getName();
	wstring getAuthor();
	UCHAR getTempo();
	TactDuration* getTactDuration();
	SHORT getTactInfoCount();
	TactInfo* getTactInfo(UCHAR number);
	CompositionInfo* getCompositionInfo() ;
	void setName(wstring name);
	void setAuthor(wstring author);
	void setTempo(UCHAR tempo);
	void setTactDuration(TactDuration tactDuration);
	Track* getTrack(UCHAR number);
	Track* addTrack(Track* track);
	void deleteTrack(UCHAR number);
	void pushTactInfo(TactInfo* tactInfo);
	void deleteTactInfo(TactInfo* tactInfo);
	void popTactInfo();
private:
	vector<Track*> tracks;
	vector<TactInfo*> tactsSchema;
	CompositionInfo compositionInfo;
};

