//LRU stands Least Recently used
/* LRU Cache Implementation (using STL)*/

#include<iostream>
#include<list>
#include<unordered_map>
#include<string>
using namespace std;

//Node of Linked List to store Data
class Node {
public:
	string key;
	int value;

	//Constructor to initialize key and value
	Node(string key, int value) {
		this->key = key;
		this->value = value;
	}
};

//LRU Cache Data Structure
class LRUCache {
public:
	list<Node>l;
	int maxSize;
	unordered_map<string, list<Node>::iterator>m;

	//Constructor to initialize maxSize

	LRUCache(int maxSize) {
		this->maxSize = maxSize > 1 ? maxSize : 1;
	}


	//insert method

	void insertKeyValue(string key, int value) {
		// 2 cases of insertion
		if (m.count(key)!=0) {
			//replace the old value and update . Cache hit occurs basically
			auto it = m[key];
			it->value = value;
		}
		else {
			//Cache Miss occurs basically
			/* 2 cases when cache miss occurs :-
			a) cache size (i.e hash map size) not full
			b) cache size full
			*/


			//check if cache is full or not
			//remove the least recently used item from cache if full

			if (l.size() == maxSize) {
				//cache full case check and erase LRU key
				Node last = l.back(); // pick last node from list as insertion order maintained in list
				m.erase(last.key); // erase same key from hashmap as well
				l.pop_back(); //remove last node from list
			}
				Node newNode = Node(key, value); // create new node using given key and value pair
				l.push_front(newNode);
				m.insert(make_pair(key, l.begin())); //or can be written as // m[key] = l.begin();
			
		}

	}

	int getValue(string key) {
		// check if that key exist or not in hashmap
		//return -1 if key not present otherwise return value corresponding to that key
		int resValue = -1;
		if (m.count(key) != 0) {
			auto it = m[key];

			resValue = it->value;

			//push in front of that list from and erase it from its previous position
			//also update address in hashmap corresponding to that key
			l.push_front(*it); //*it gives value of that node and it gives address to that node
			l.erase(it);
			m[key] = l.begin();
		}
		return resValue;
	}

	string mostRecentKey() {
		// return NULL if list is empty otherwise return most recent key
		if (l.size() > 0) {
			return l.front().key;
		}
		return NULL;
	}
};


int main() {
	//driver function for checking LRU Cache Implementation

	LRUCache lru(3); // creating LRU of size 3

	lru.insertKeyValue("mango", 10);
	lru.insertKeyValue("apple", 20);
	lru.insertKeyValue("guava", 30);
	cout << lru.mostRecentKey() << endl;

	lru.insertKeyValue("mango", 40);
	cout << lru.mostRecentKey() << endl;


	//check mango value
	int value = lru.getValue("mango");
	if (value != -1) {
		cout << "Order of Mango : " << value << endl;
	}


	lru.insertKeyValue("banana", 20);

	if (lru.getValue("apple") == -1) {
		cout << "apple doesn't exist"<<endl;
	}

	if (lru.getValue("mango") == -1) {
		cout << "mango doesn't exist" << endl;
	}

	if (lru.getValue("guava") == -1) {
		cout << "guava doesn't exist" << endl;
	}

	if (lru.getValue("banana") == -1) {
		cout << "banana doesn't exist" << endl;
	}

	return 0;
}