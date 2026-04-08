#include "SetIterator.h"
#include "Set.h"
#include <exception>


SetIterator::SetIterator(const Set& m) : set(m) //first
{
	//TODO - Implementation
	currentPos = 0;
	while (currentPos < set.capacity && !set.elems[currentPos]) {
		currentPos++;
	}
}

void SetIterator::first() { //best: Theta(1), worst: Theta(capacity), avg: Theta(capacity)
	//TODO - Implementation
	currentPos = 0;
	while (currentPos < set.capacity && !set.elems[currentPos]) { //Cat timp nu am iesit din array si casuta curenta contine false, fa un pas mai departe.
		currentPos++;
	}
}


void SetIterator::next() { //best: Theta(1), worst: Theta(capacity), avg: Theta(capacity)
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	currentPos++;
	while (currentPos < set.capacity && !set.elems[currentPos]) {
		currentPos++;
	}
}


TElem SetIterator::getCurrent() //Theta(1)
{
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	return set.offset + currentPos;
}

bool SetIterator::valid() const { //Theta(1)
	//TODO - Implementation
	return currentPos < set.capacity;
}

void SetIterator::step(int k) { // best: Theta(k), worst: Theta(capacity), avg: O(capacity)
	if (currentPos < 0 || currentPos >= set.capacity) {
		throw std::exception();
	}

	if (k==0) {
		return;
	}

	if (k > 0) {
		for (int i = 0; i < k; i++) {
			currentPos++;
			while (currentPos < set.capacity && !set.elems[currentPos]) {
				currentPos++;
			}
			if (currentPos >= set.capacity) {
				break;
			}
		}
	}else {
		int pasi_reali = -k;
		for (int i = 0; i < pasi_reali; i++) {
			currentPos--;
			while (currentPos >= 0 && !set.elems[currentPos]) {
				currentPos--;
			}
			if (currentPos < 0) {
				currentPos = set.capacity;
				break;
			}
		}
	}
}
