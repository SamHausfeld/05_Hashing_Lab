//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/07/24
#include "USet.h"

/*
* Note: Just above your template declaration when you use this class, you
* must define method called "hash" that takes a Key as input, and returns
* an unsigned long (which is the hash value)
*
* For example, you might do:
* unsigned long hash(char c){ return 10*((unsigned long)c)%13; }
* HashTable<char,int> mySillyTable;
*
* If you don't define an appropriate hash function, the class won't compile.
*/

template <class Key, class T>
class HashTable : public USet < Key, T > {
private:
	class HashRecord {
	public:
		Key k;
		T x;

		//If the slot in the hash table is totally empty, set this to true.
		bool isNull;

		//If the slot used to have something in it, but doesn't now, set
		// isDel to true, and isNull to false. isNull is only for slots
		// that have never been used
		bool isDel;

		HashRecord() { isNull = true; isDel = false; };
	};

public:
	//See USet.h for documentation of these methods
	virtual unsigned long size();
	virtual void add(Key k, T x);
	virtual void remove(Key k);
	virtual T find(Key k);
	virtual bool keyExists(Key k);

	//Initialize all private member variables.
	HashTable();
	//Delete any dynamically allocated memory.
	virtual ~HashTable();

private:
	//A pointer to the array that holds the hash table data
	HashRecord* backingArray;

	//Whenever numItems + numRemoved >= backingArraySize/2, call
	// grow(). grow() should make a new backing array that is twice the
	// size of the old one, similar to what we did in the ArrayQueue
	// lab.
	//Note: You cannot just loop through the old array and copy it to the
	// new one! Since the backing array size has changed, each item will likely
	// map to a different slot in the array. You may just want to use add()
	// after initializing the new array.
	void grow();

	//This helper method should take a key, and return the index for that
	// item within the hash table. If the item already exists, return the
	// index of the existing item. If the item doesn't exist, return the index
	// where it OUGHT to be. This function can then be used as a helper method in
	// your other methods.
	unsigned long calcIndex(Key k);

	unsigned long numItems; //Number of items in the hash table

	//Note: Ordinarily, these OUGHT to be private. In this case I have
	// made them public for easy of testing.
public:
	unsigned long numRemoved; //Number of slots that have been removed but not re-used. Those that have isDel == true
	unsigned long backingArraySize;
};

//You will need this so you can make a string to throw in
// remove
// Originality Statement: I regret to state that I struggled immensely with this code.  I sought much help from many people, and a lot of my code is extremely similar to fellow classmates.
// I wish only to improve my ability and understanding of the code below in the next week or so, I regret not being prepared whatsoever for this.
#include <string>

template <class Key, class T>
HashTable<Key, T>::HashTable(){
	//backingArray = new HashRecord[hashPrimes[0]];
	//backingArraySize = hashPrimes[0];
	//numRemoved = 0;
	//numItems = 0;

	// The HashTable class has 4 variables in it:
	// backingArray: A backing array to store the HashRecords in,
	// backingArraySize: a long to keep track of the size of that array,
	// numItems: a long to keep track of the amount of things in the HashTable,
	// and numRemoved: a long to keep track of the number of spaces in the array that have been used, but not reused? These spaces can be overwritten


	// Need to create an array of Lists
	// except they aren't lists, they're HashRecords..
	// Which is a subclass of HashTable with all the vitals in order.
	// These vitals being: a key, an object, isDel = false and isNull = true.
	// And we want the length to be prime so we can hash properly
	// So we'll use the hashPrimes array, the first entry in which is 53.
	backingArray = new HashRecord[hashPrimes[0]];
	backingArraySize = hashPrimes[0];
	numItems = 0;
	numRemoved = 0;


}

template <class Key, class T>
HashTable<Key, T>::~HashTable() {
	delete[] backingArray;
}


// Given a key K,
// Return where it ought to be, or where it already is 
template <class Key, class T>
unsigned long HashTable<Key, T>::calcIndex(Key k){
	//unsigned long i = hash(k);
	//for (i; true; i++) {
	//	if (backingArray[i % backingArraySize].isNull || backingArray[i % backingArraySize].k == k){
	//		return (i % backingArraySize);
	//	}
	//}
	//return numItems; // to indicate failure

	unsigned long i = hash(k) % backingArraySize;
	// increment and search for a match or suitable index
	unsigned long x = -1;
	for (i; true; i = (i + 1) % backingArraySize) {
		//if (backingArray[i].k == k || backingArray[i].isNull || backingArray[i].isDel)
		//	return i;
		if (backingArray[i].isDel)
			x = i;
		if (backingArray[i].isNull) {
			if (x == -1) return i;
			else return x;
		}
		if (backingArray[i].k == k && !backingArray[i].isDel && !backingArray[i].isNull) 
			return i;
	}
	return x;

}

template <class Key, class T>
void HashTable<Key, T>::add(Key k, T x){
	// Original Code
	//if ((numItems + numRemoved) >= backingArraySize / 2){
	//	grow();
	//}
	//unsigned long i = hash(k);
	//for (i; true; i++) {
	//	if (backingArray[i % backingArraySize].isNull || backingArray[i % backingArraySize].k == k || backingArray[i % backingArraySize].isDel){
	//		i = (i % backingArraySize);
	//		break;
	//	}
	//}
	//backingArray[i].k = k;
	//backingArray[i].x = x;
	//backingArray[i].isNull = false;
	//backingArray[i].isDel = false;
	//numItems++;

	// First things first, grow if you need to.
	// AKA, grow if the array is more than half full!
	if (2 * (numItems + numRemoved + 1) > backingArraySize) {
		grow();
	}
	// Now I hash the key to get the index in the "circular" array.
	// You write in any location that is marked null or del
	// or if you find a cell with the same key??
	// so find the closest example of that.
	unsigned long i = hash(k) % backingArraySize;
	//for (i; true; i = (i + 1) % backingArraySize){
	//	if (backingArray[i].k == k) {
	//		break;
	//	}

	//}

	i = calcIndex(k);
	if (backingArray[i].isNull) {
		numItems++;
	}
	if (backingArray[i].isDel) {
		numRemoved--;
		numItems++;
	}
	


	// Once a suitable cell is found, add it by assigning it's variables to the variables of the object added.
	backingArray[i].k = k; // Assign the key.
	backingArray[i].x = x; // Assign the object.
	backingArray[i].isDel = false;
	backingArray[i].isNull = false; // Don't let it be touched for now!
}
template <class Key, class T>
void HashTable<Key, T>::remove(Key k){
	//// Set the element at spot k to del
	//if (keyExists(k)) {
	//	backingArray[calcIndex(k)].isDel = true;
	//	numRemoved++;
	//	numItems--;
	//}
	
	if (keyExists(k) == false) throw std::string("Can't remove something that doesn't exist!");

	backingArray[calcIndex(k)].isDel = true;
	numItems--;
	numRemoved++;


}

template <class Key, class T>
T HashTable<Key, T>::find(Key k){
	////T dummy;
	//if (keyExists(k)){
	//	return (backingArray[calcIndex(k)].x);
	//}
	//else throw std::string("Can't find() a key like that in the table!");
	////return dummy;

	if (keyExists(k) == false)
		throw std::string("Can't find something that doesn't exist!");
	else return backingArray[calcIndex(k)].x;



}


template <class Key, class T>
bool HashTable<Key, T>::keyExists(Key k){
	//for (int j = 0; j < backingArraySize; j++){
	//	if (backingArray[j].k == k && !backingArray[j].isDel)
	//		return true;
	//}
	//return false;

	unsigned long i = calcIndex(k);
	if (backingArray[i].isNull) 
		return false;
	if (backingArray[i].isDel) 
		return false;
	if (backingArray[i].k == k)
		return true;

	return false;

}

template <class Key, class T>
unsigned long HashTable<Key, T>::size(){
	return numItems;
}

template <class Key, class T>
void HashTable<Key, T>::grow(){
	HashRecord* formerArray = backingArray;
	int formerArraySize = backingArraySize;
	for (int i = 0; true; i++) {
		if (hashPrimes[i] == backingArraySize) {
			backingArray = new HashRecord[hashPrimes[i + 1]];
			backingArraySize = hashPrimes[i + 1];
			break;
		}
	}
	numItems = 0;
	numRemoved = 0;
	for (int i = 0; i < formerArraySize; i++) {
		if (!formerArray[i].isNull && !formerArray[i].isDel) {
			add(formerArray[i].k, formerArray[i].x);
		}
	}
	delete[] formerArray;


}
