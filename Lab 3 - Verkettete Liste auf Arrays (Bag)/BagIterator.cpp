#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c) //Theta(1)
{
	//TODO - Implementation
	this->current = bag.head;
	this->currentFreq = 1;
}

void BagIterator::first() { //Theta(1)
	//TODO - Implementation
	this->current = bag.head;
	this->currentFreq = 1;
}

void BagIterator::next() { //Theta(1)
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	this->currentFreq++;
	if (this->currentFreq > bag.elements[this->current].freq) {
		this->current = bag.next[this->current];
		this->currentFreq = 1;
	}
}

bool BagIterator::valid() const { //Theta(1)
	return this->current != -1;
}

TElem BagIterator::getCurrent() const //Theta(1)
	//TODO - Implementation
{
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	return bag.elements[this->current].elem;
}
