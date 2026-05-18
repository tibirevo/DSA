#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d) //Theta(1)
{
	//TODO - Implementation
	this->current = d.head;
}


void MapIterator::first() { //Theta(1)
	//TODO - Implementation
	this->current = map.head;
}


void MapIterator::next() { //Theta(1)
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	this->current = this->current->next;
}


TElem MapIterator::getCurrent(){ //Theta(1)
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	return this->current->info;
}


bool MapIterator::valid() const { //Theta(1)
	//TODO - Implementation
	return this->current != nullptr;
}
