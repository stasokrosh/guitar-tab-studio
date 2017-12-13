#pragma once
template <class T>
class InstrumentFactory {
public:
	virtual BOOL initialize() = 0;
	virtual T* createInstrument(wstring name) = 0;
	virtual vector<wstring> getInstrumentNames() = 0;
};