#include "Set.h"
#include "SetIterator.h"

Set::Set() {
	elems=nullptr;
	capacity=0;
	offset=0;
	nrElements=0;
}


bool Set::add(TElem elem) {  //best: Theta(1), worst: Theta(n), avg: Theta(1)
	//Verificam daca elementul este in limitele curente.
	if (capacity > 0 && elem >= offset && elem < offset + capacity) {
		if (elems[elem - offset]) {
			return false; //Elementul exista deja
		}
	}
	//Daca iesim din limite, redimensionam si centram datele
	if (capacity == 0 || elem < offset || elem >= offset + capacity) {
		// 1. Gasim minimul si maximul absolut care trebuie sa incapa
		int actual_min = elem;
		int actual_max = elem;

		if (nrElements > 0) {
			for (int i = 0; i < capacity; i++) {
				if (elems[i]) {
					int val = offset + i;
					if (val < actual_min) actual_min = val;
					break;
				}
			}
			for (int i = capacity - 1; i >= 0; i--) {
				if (elems[i]) {
					int val = offset + i;
					if (val > actual_max)actual_max	= val;
					break;
				}
			}
		}
		int needed_capacity = actual_max - actual_min + 1;

		// 2. Dublam capacitatea curenta pana acoperim necesarul.
		int new_capacity = (capacity == 0) ? 1 : capacity;
		while (new_capacity < needed_capacity) {
			new_capacity *= 2;
		}

		// 3. Calculam noul offset pentru a CENTRA elementele
		//Lasam jumatate din spatiul gol la stanga, jumatate la dreapta
		int extra_space = new_capacity - needed_capacity;
		int new_offset = actual_min - (extra_space / 2);

		// 4. Alocam noul array si il curatam.
		bool* new_elems = new bool[new_capacity];
		for (int i = 0; i < new_capacity; i++) {
			new_elems[i] = false;
		}

		// 5. Copiem valorile vechi.
		if (elems != nullptr) {
			for (int i = 0; i < capacity; i++) {
				if (elems[i]) {
					new_elems[offset + i - new_offset] = true;
				}
			}
			delete[] elems; //Eliberam memoria.
		}

		// 6. Actualizam starea Set-ului.
		elems = new_elems;
		capacity = new_capacity;
		offset = new_offset;
	}

	//Adaugam elementul propriu-zis.
	elems[elem - offset] = true;
	nrElements++;
	return true;
}


bool Set::remove(TElem elem) { //best: Theta(1), worst: Theta(1), avg: Theta(1)
	//TODO - Implementation
	if (capacity == 0 || elem < offset || elem >= offset + capacity) {
		return false;
	}

	if (elems[elem - offset]) {
		elems[elem - offset] = false;
		nrElements--;
		return true;
	}
	return false;
}

bool Set::search(TElem elem) const {  //Theta(1)
	//TODO - Implementation
	if (capacity == 0 || elem < offset || elem >= offset + capacity) {
		return false;
	}
	return elems[elem - offset];
}


int Set::size() const { //Theta(1)
	//TODO - Implementation
	return nrElements;
}


bool Set::isEmpty() const { //Theta(1)
	//TODO - Implementation
	return nrElements == 0;
}


Set::~Set() { //Theta(1)
	//TODO - Implementation
	delete[] elems;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
