#include "Map.h"
#include "MapIterator.h"

Map::Map() { //Theta(1)
	//TODO - Implementation
	this->head = nullptr;
	this->tail = nullptr;
	this->count = 0;
}

Map::~Map() { //Theta(n)
	//TODO - Implementation
	DLLNode* current = this->head;
	while (current != nullptr) {
		DLLNode* nextNode = current->next;
		delete current;
		current = nextNode;
	}
}

TValue Map::add(TKey c, TValue v){ //best: Theta(1), worst: Theta(n), avg: O(n)
	//TODO - Implementation
	DLLNode* current = this->head;
	while (current != nullptr) {
		if (current->info.first == c) {
			TValue oldValue = current->info.second;
			current->info.second = v;
			return oldValue;
		}
		current = current->next;
	}

	DLLNode* newNode = new DLLNode;
	newNode->info.first = c;
	newNode->info.second = v;

	newNode->next = this->head;
	newNode->prev = nullptr;

	if (this->head != nullptr) {
		this->head->prev = newNode;
	}else {
		this->tail = newNode;
	}

	this->head = newNode;
	this->count++;
	return NULL_TVALUE;
}

TValue Map::search(TKey c) const{ //best: Theta(1), worst: Theta(n), avg: O(n)
	//TODO - Implementation
	DLLNode* current = this->head;
	while (current != nullptr) {
		if (current->info.first == c) {
			return current->info.second;
		}
		current = current->next;
	}
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){ //best: Theta(1), worst: Theta(n), avg: O(n)
	//TODO - Implementation
	DLLNode* current = this->head;
	while (current != nullptr) {
		if (current->info.first == c) {
			TValue valueToReturn = current->info.second;
			if (current == this->head) {
				this->head = current->next;
				if (this->head != nullptr) {
					this->head->prev = nullptr;
				}else {
					this->tail = nullptr;
				}
			}
			else if (current == this->tail) {
				this->tail = current->prev;
				this->tail->next = nullptr;
			}
			else {
				current->prev->next = current->next;
				current->next->prev = current->prev;
			}
			delete current;
			this->count--;
			return valueToReturn;
		}
		current = current->next;
	}
	return NULL_TVALUE;
}

bool Map::isSubsetOf(const Map &other) const { //best: Theta(m), worst: Theta(n * m), avg: O(n * m)
	DLLNode* currentThis = this->head;
	while (currentThis != nullptr) {
		bool foundMatch = false;
		DLLNode* currentOther = other.head;
		while (currentOther != nullptr) {
			if (currentOther->info.first == currentThis->info.first) {
				if (currentOther->info.second == currentThis->info.second) {
					foundMatch = true;
				}
				break;
			}
			currentOther = currentOther->next;
		}
		if (foundMatch == false) {
			return false;
		}
		currentThis = currentThis->next;
	}
	return true;
}

int Map::size() const { //Theta(1)
	//TODO - Implementation
	return this->count;
}

bool Map::isEmpty() const{ //Theta(1)
	//TODO - Implementation
	return this->count == 0;
}

MapIterator Map::iterator() const { //Theta(1)
	return MapIterator(*this);
}
