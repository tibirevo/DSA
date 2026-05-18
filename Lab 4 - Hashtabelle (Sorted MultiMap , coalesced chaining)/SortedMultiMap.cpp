#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

int SortedMultiMap::hash(TKey key) const { //Theta(1)
	int h = key % capacity;
	if (h < 0) {
		h += capacity;
	}
	return h;
}

void SortedMultiMap::updateFirstEmpty() { //best: Theta(1), worst: Theta(m), avg: Theta(1)
	firstEmpty--;
	while (firstEmpty >= 0 && elements[firstEmpty].info.first != NULL_TVALUE) {
		firstEmpty--;
	}
}

void SortedMultiMap::resize() { //Theta(m + n)
	int oldCapacity = capacity;
	capacity = capacity * 2;
	HashNode* oldElements = elements;

	elements = new HashNode[capacity];
	for (int i = 0; i < capacity; i++) {
		elements[i].info.first = NULL_TVALUE;
		elements[i].info.second = NULL_TVALUE;
		elements[i].next = -1;
	}

	firstEmpty = capacity - 1;
	count = 0;

	for (int i = 0; i < oldCapacity; i++) {
		if (oldElements[i].info.first != NULL_TVALUE) {
			this->add(oldElements[i].info.first, oldElements[i].info.second);
		}
	}
	delete[] oldElements;
}

SortedMultiMap::SortedMultiMap(Relation r) { //Theta(m)
	//TODO - Implementation
	this->rel = r;
	this->capacity = 13;
	this->count = 0;
	this->firstEmpty = capacity - 1;

	this->elements = new HashNode[capacity];
	for (int i = 0; i < capacity; i++) {
		elements[i].info.first = NULL_TVALUE;
		elements[i].info.second = NULL_TVALUE;
		elements[i].next = -1;
	}
}

void SortedMultiMap::add(TKey c, TValue v) { //best: Theta(1), worst: Theta(n), avg: Theta(1)
	//TODO - Implementation
	if (count == capacity) {
		resize();
	}

	int current = hash(c);

	if (elements[current].info.first == NULL_TVALUE) {
		elements[current].info.first = c;
		elements[current].info.second = v;
		elements[current].next = -1;

		if (current == firstEmpty) {
			updateFirstEmpty();
		}
		count++;
		return;
	}

	while (elements[current].next != -1) { //mergem la ultimul element
		current = elements[current].next;
	}

	elements[firstEmpty].info.first = c;
	elements[firstEmpty].info.second = v;
	elements[firstEmpty].next = -1;

	elements[current].next = firstEmpty; //facem legatura intre elemente sa arate spre cel corect
	count++;
	updateFirstEmpty();
}

vector<TValue> SortedMultiMap::search(TKey c) const { //best: Theta(1), worst: Theta(n), avg: Theta(1)
	//TODO - Implementation
	std::vector<TValue> result;
	int current = hash(c);

	while (current != -1) {
		if (elements[current].info.first == c) {
			result.push_back(elements[current].info.second);
		}
		current = elements[current].next;
	}
	return result;
}

bool SortedMultiMap::remove(TKey c, TValue v) { //best: Theta(1), worst: Theta(n), avg: Theta(1)
	//TODO - Implementation
    int i = hash(c); //gaura curenta
	int j = -1; //prev gaura

	while (i != -1 && (elements[i].info.first != c || elements[i].info.second != v)) {
		j = i;
		i = elements[i].next;
	}

	if (i == -1) {
		return false;
	}

	bool over = false;
	do {
		int p = elements[i].next; //candidat inlocuire
		int pp = i; //prev canddidat

		while (p != -1 && hash(elements[p].info.first) != hash(elements[i].info.first)) {
			pp = p;
			p = elements[p].next;
		}

		if (p == -1) {
			over = true;
		}else {
			elements[i].info = elements[p].info;
			i = p;
			j = pp;
		}
	}while (!over);

	if (j != -1) {
		elements[j].next = elements[i].next;
	}

	elements[i].info.first = NULL_TVALUE;
	elements[i].info.second = NULL_TVALUE;
	elements[i].next = -1;
	count--;

	if (i > firstEmpty) {
		firstEmpty = i;
	}

	return true;
}


int SortedMultiMap::size() const { //Theta(1)
	//TODO - Implementation
	return count;
}

bool SortedMultiMap::isEmpty() const { //Theta(1)
	//TODO - Implementation
	return count == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() { //Theta(1)
	//TODO - Implementation
	delete[] elements;
}

ValueIterator::ValueIterator(const SortedMultiMap &m, TKey k) : map(m), targetKey(k) { //best: Theta(1), worst: Theta(n), avg: Theta(1)
	first();
}

void ValueIterator::first() { //best: Theta(1), worst: Theta(n), avg: Theta(1)
	int h = targetKey % map.capacity;
	if (h < 0) {
		h += map.capacity;
	}

	currentPos = h;
	while (currentPos != -1 && map.elements[currentPos].info.first != targetKey) {
		currentPos = map.elements[currentPos].next;
	}
}

void ValueIterator::next() { //best: Theta(1), worst: Theta(n), avg: Theta(1)
	if (!valid()) {
		throw std::exception();
	}

	currentPos = map.elements[currentPos].next;
	while (currentPos != -1 && map.elements[currentPos].info.first != targetKey) {
		currentPos = map.elements[currentPos].next;
	}
}

TValue ValueIterator::getCurrent() const { //Theta(1)
	if (!valid()) {
		throw std::exception();
	}

	return map.elements[currentPos].info.second;
}

bool ValueIterator::valid() const { //Theta(1)
	return currentPos != -1;
}
