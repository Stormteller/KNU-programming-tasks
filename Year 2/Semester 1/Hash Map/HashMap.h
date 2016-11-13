#pragma once
#include <functional>

//Hash-table node
template <typename K, typename V>
class Node {
private:
	// key-value pair
	K key;
	V value;
	Node* next;

public:
	Node(K keyData, V valueData)  {
		key = keyData;
		value = valueData;
		next = NULL;
	}

	K getKey() const {
		return key;
	}

	V getValue() const {
		return value;
	}

	void setValue(V value) {
		this->value = value;
	}

	Node* getNext() const {
		return next;
	}

	void setNext(Node* next) {
		this->next = next;
	}
};


template <typename K, typename V>
class HashMap {
private:
	Node<K, V> **table;
	const int TABLE_SIZE = 31;	//Size of table | Prime number to reduce collisions

public:
	HashMap();

	~HashMap();

	//Get value by key, return true if key exist, flase if not
	bool get(const K &key, V &value);

	//Create key-value pair
	void put(const K &key, const V &value);

	//Remove key-value pair by key
	void remove(const K &key);

};

template<typename K, typename V>
HashMap<K, V>::HashMap() {
	table = new Node<K, V> *[TABLE_SIZE]();
}

template<typename K, typename V>
HashMap<K, V>::~HashMap() {
	for (int i = 0; i < TABLE_SIZE; ++i) {

		Node<K, V> *entry = table[i];
		while (entry != NULL) {
			Node<K, V> *prev = entry;
			entry = entry->getNext();
			delete prev;
		}
		table[i] = NULL;

	}
	delete[] table;
}

template<typename K, typename V>
void HashMap<K, V>::remove(const K &key) {
	unsigned long hashValue = std::hash<K>()(key) % TABLE_SIZE;	//Hash value for key
	Node<K, V> *prev = NULL;
	Node<K, V> *entry = table[hashValue];

	//Find key in the list with same hash
	while (entry != NULL && entry->getKey() != key) {
		prev = entry;
		entry = entry->getNext();
	}

	if (entry == NULL) {
		return;
	}
	else {
		if (prev == NULL) {
			table[hashValue] = entry->getNext();
		}
		else {
			prev->setNext(entry->getNext());
		}
		delete entry;
	}
}


template<typename K, typename V>
void HashMap<K, V>::put(const K &key, const V &value) {
	unsigned long hashValue = std::hash<K>()(key) % TABLE_SIZE;	//Hash value for key
	Node<K, V> *prev = NULL;
	Node<K, V> *entry = table[hashValue];	//Array cell that matches the hash

	//Find key in the list with same hash
	while (entry != NULL && entry->getKey() != key) {
		prev = entry;
		entry = entry->getNext();
	}

	//If key dont exist put pair to the end of list in cell
	if (entry == NULL) {
		entry = new Node<K, V>(key, value);
		if (prev == NULL) {
			table[hashValue] = entry;
		}
		else {
			prev->setNext(entry);
		}
	}
	else {
		//If key exist update value
		entry->setValue(value);
	}
}

template<typename K, typename V>
bool HashMap<K, V>::get(const K &key, V &value) {
	unsigned long hashValue = std::hash<K>()(key) % TABLE_SIZE; //Hash value for key
	Node<K, V> *entry = table[hashValue];

	//If key exist save value and return true
	while (entry != NULL) {
		if (entry->getKey() == key) {
			value = entry->getValue();
			return true;
		}
		entry = entry->getNext();
	}

	//Return false if key is not found
	return false;
}