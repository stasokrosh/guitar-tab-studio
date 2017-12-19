#pragma once
#include "TactIterator.h"
#include "TactFactory.h"
#include <vector>

using namespace std;


template <class T>
class TactIteratorTemplate : public TactIterator {
public:
	TactIteratorTemplate(vector<T*>* tacts, SHORT num, TactFactory* tactFactory) {
		this->tacts = tacts;
		this->num = num;
		this->tactFactory = tactFactory;
	}
	virtual Tact* getTact() {
		if (num == this->tacts->size()) {
			return NULL;
		} else {
			return this->tacts->at(this->num);
		}
	}
	T* getTemplateTact() {
		if (num == this->tacts->size()) {
			return NULL;
		} else {
			return this->tacts->at(this->num);
		}
	}
	virtual void deleteTact() {
		vector<T*>::iterator iterator = this->getIterator();
		this->tacts->erase(iterator);
		this->num--;
	}
	virtual void moveForward() {
		this->num++;
	}
	virtual void moveBackwards() {
		this->num--;
	}
	virtual void insertTact(TactInfo* tactInfo) {
		vector<T*>::iterator iterator = this->getIterator();
		iterator++;
		this->tacts->insert(iterator, reinterpret_cast<T*>(tactFactory->createTact(tactInfo)));
	}
	virtual BOOL isLast() {
		return this->num == this->tacts->size() - 1;
	}
	virtual BOOL isFirst() {
		return this->num == 0;
	}
private:
	vector<T*>* tacts;
	SHORT num;
	TactFactory* tactFactory;

	typename vector<T*>::iterator getIterator() {
		SHORT i = 0;
		vector<T*>::iterator iterator = this->tacts->begin();
		while (i < this->num) {
			iterator++;
		}
		return iterator;
	}
};

