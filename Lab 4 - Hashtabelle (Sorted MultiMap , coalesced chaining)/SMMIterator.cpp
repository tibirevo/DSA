#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){ //Theta(m + n^2)
	//TODO - Implementation
	this->totalElements = map.size();

	if (this->totalElements > 0) {
		this->sortedArray = new TElem[this->totalElements];
		int index = 0;
		for (int i = 0; i < map.capacity; i++) {
			if (map.elements[i].info.first != NULL_TVALUE) {
				this->sortedArray[index] = map.elements[i].info;
				index++;
			}
		}

		for (int i = 0; i < this->totalElements - 1; i++) {
			for (int j = i + 1; j < this->totalElements; j++) {
				if (!map.rel(this->sortedArray[i].first, this->sortedArray[j].first)) {
					TElem aux = this->sortedArray[i];
					this->sortedArray[i] = this->sortedArray[j];
					this->sortedArray[j] = aux;
				}
			}
		}
	}else {
		this->sortedArray = nullptr;
	}

	this->currentPosition = 0;
}

void SMMIterator::first(){ //Theta(1)
	//TODO - Implementation
	this->currentPosition = 0;
}

void SMMIterator::next(){ //Theta(1)
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}

	this->currentPosition++;
}

bool SMMIterator::valid() const{ //Theta(1)
	//TODO - Implementation
	return this->currentPosition < this->totalElements;
}

TElem SMMIterator::getCurrent() const{ //Theta(1)
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}

	return this->sortedArray[this->currentPosition];
}

SMMIterator::~SMMIterator() { //Theta(1)
	if (this->sortedArray != nullptr) {
		delete[] this->sortedArray;
	}
}
