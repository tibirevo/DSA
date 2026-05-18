#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class ValueIterator;

class SortedMultiMap {
	friend class SMMIterator;
	friend class ValueIterator;
    private:
		//TODO - Representation
	struct HashNode {
		TElem info;
		int next;
	};
	HashNode* elements;
	int capacity;
	int count;
	int firstEmpty;
	Relation rel;

	int hash(TKey key) const;
	void updateFirstEmpty();
	void resize();

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};

class ValueIterator {
private:
	const SortedMultiMap& map;
	TKey targetKey;
	int currentPos;
public:
	ValueIterator(const SortedMultiMap& m, TKey k);
	void first();
	void next();
	bool valid() const;
	TValue getCurrent() const;
};