#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

void Bag::resize() { //Theta(capacity)
	int newCapacity = capacity * 2;
	NodeData* newElements = new NodeData[newCapacity];
	int* newNext = new int[newCapacity];
	int* newPrev = new int[newCapacity];

	for (int i = 0; i < capacity; i++) {
		newElements[i] = elements[i];
		newNext[i] = next[i];
		newPrev[i] = prev[i];
	}

	for (int i = capacity; i < newCapacity - 1; i++) {
		newNext[i] = i + 1;
	}
	newNext[newCapacity - 1] = -1;

	firstFree = capacity;
	capacity = newCapacity;
	delete[] elements;
	delete[] next;
	delete[] prev;

	elements = newElements;
	next = newNext;
	prev = newPrev;
}

int Bag::allocateP() { //Theta(1)
	if (firstFree == -1) {
		resize();
	}
	int newFreePos = firstFree;
	firstFree = next[firstFree];
	return newFreePos;
}

void Bag::freeP(int i) { //Theta(1)
	next[i] = firstFree;
	firstFree = i;
}

Bag::Bag() { //Theta(capacity)
	//TODO - Implementation
	capacity = 10;
	elements = new NodeData[capacity];
	next = new int[capacity];
	prev = new int[capacity];

	head = -1;
	tail = -1;
	totalSize = 0;
	for (int i = 0; i < capacity - 1; i++) {
		next[i] = i + 1;
	}
	next[capacity - 1] = -1;
	firstFree = 0;
}


void Bag::add(TElem elem) { //best: Theta(1), worst: Theta(n), avg: Theta(n)
	//TODO - Implementation
	int current = head;
	while (current != -1) {
		if (elements[current].elem == elem) {
			elements[current].freq++;
			totalSize++;
			return;
		}
		current = next[current];
	}
	int newNode = allocateP();
	elements[newNode].elem = elem;
	elements[newNode].freq = 1;
	prev[newNode] = tail;
	next[newNode] = -1;

	if (head == -1) {
		head = newNode;
		tail = newNode;
	}else {
		next[tail] = newNode;
		tail = newNode;
	}
	totalSize++;
}


bool Bag::remove(TElem elem) { //best: Theta(1), worst: Theta(n), avg: Theta(n)
	//TODO - Implementation
	int current = head;
	while (current != -1) {
		if (elements[current].elem == elem) {
			elements[current].freq--;
			totalSize--;
			if (elements[current].freq == 0) {
				if (prev[current] != -1) {
					next[prev[current]] = next[current];
				}else {
					head = next[current];
				}
				if (next[current] != -1) {
					prev[next[current]] = prev[current];
				}else {
					tail = prev[current];
				}
				freeP(current);
			}
			return true;
		}
		current = next[current];
	}
	return false;
}


bool Bag::search(TElem elem) const { //best: Theta(1), worst: Theta(n), avg: Theta(n)
	//TODO - Implementation
	int current = head;
	while (current != -1) {
		if (elements[current].elem == elem) {
			return true;
		}
		current = next[current];
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const { //best: Theta(1), worst: Theta(n), avg: Theta(n)
	//TODO - Implementation
	int current = head;
	while (current != -1) {
		if (elements[current].elem == elem) {
			return elements[current].freq;
		}
		current = next[current];
	}
	return 0;
}


int Bag::size() const { //Theta(1)
	//TODO - Implementation
	return totalSize;
}


bool Bag::isEmpty() const { //Theta(1)
	//TODO - Implementation
	return totalSize == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() { //Theta(1)
	//TODO - Implementation
	delete[] elements;
	delete[] next;
	delete[] prev;
}

bool Bag::operator==(const Bag & other) const { //best: Theta(1), worst: Theta(n * m), avg: Theta(n * m)
	if (this->totalSize != other.totalSize) {
		return false;
	}

	int currentThis = this->head;
	while (currentThis != -1) {
		TElem elementCautat = this->elements[currentThis].elem;
		int frecventaCautata = this->elements[currentThis].freq;
		bool gasitExact = false;
		int currentOther = other.head;
		while (currentOther != -1) {
			if (other.elements[currentOther].elem == elementCautat) {
				if (other.elements[currentOther].freq == frecventaCautata) {
					gasitExact = true;
				}
				break;
			}
			currentOther = other.next[currentOther];
		}
		if (gasitExact == false) {
			return false;
		}
		currentThis = this->next[currentThis];
	}
	return true;
}
