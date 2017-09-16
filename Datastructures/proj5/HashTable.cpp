#include "HashTable.h"
#include "primes.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

char * const HashTable::DELETED = (char *)1;

HashTable::HashTable(HashTable& other) {
	if (other.isRehashing())
		other.forceRehash();

	this->table = new char*[other.tableSize(1)];
	this->capacity = other.tableSize(1);
	this->occupancy = 0;

	this->oldTable = NULL;
	this->otCapacity = 0;
	this->otOccupancy = 0;

	//From index 0 to tableSize, if not null and not deleted strdup and insert into the table
	for (int i = 0; i < this->capacity; i++) {
		if (other.at(i, 0) != NULL && other.at(i, 0) != DELETED) {
			this->occupancy++;
			this->table[i] = strdup(other.at(i, 0));
		} 
		
		//Otherwise if its deleted, set it to deleted in new table
		else if (other.at(i, 0) == DELETED)
			this->table[i] = DELETED;
		//Else initialize it to null
		else
			this->table[i] = NULL;
	}

}

const HashTable& HashTable::operator= (HashTable& rhs){
	//Remove all items from old table, if it exists
	if (this->oldTable != NULL) {
		for (int i = 0; i < this->otCapacity; i++) {
			//If not null, set to null
			if (this->oldTable[i] != NULL) {
				//if not DELETED, free the memory
				if (this->oldTable[i] != DELETED)
					free(this->oldTable[i]);
				this->oldTable[i] = NULL;
			}
		}
		//delete array
		delete[] this->oldTable;
	}

	//for all items in table
	for (int i = 0; i < this->capacity; i++) {
		//If not null, set to null
		if (this->table[i] != NULL) {
			//if not deleted, free the memory
			if (this->table[i] != DELETED)
				free(this->table[i]);
			this->table[i] = NULL;
		}
	}
	//delete array
	delete[] this->table;

	//force rehash to finish if needed on rhs
	if (rhs.isRehashing())
		rhs.forceRehash();

	//new table for this of size equal to the other's size
	this->table = new char*[rhs.tableSize(1)];

	//reset old table
	this->oldTable = NULL;
	this->otCapacity = 0;
	this->otOccupancy = 0;
	this->occupancy = 0;
	this->capacity = rhs.tableSize(1);

	//for all items in the rhs table
	for (int i = 0; i < this->capacity; i++) {
		//if not deleted and not null, strdup and insert into table at i
		if (rhs.at(i, 0) != NULL && rhs.at(i, 0) != DELETED) {
			this->table[i] = strdup(rhs.at(i, 0));
			this->occupancy++;
		}
		//If DELETED set to DELETED
		else if (rhs.at(i, 0) == DELETED)
			this->table[i] = DELETED;

		//Otherwise set to NULL
		else
			this->table[i] = NULL;
	}

	return *this;
}

void HashTable::forceRehash() {
	for (int i = 0; i < this->otCapacity; i++) {
		if (this->oldTable[i] != NULL) {
			if (this->oldTable[i] != DELETED) {
				this->insert(this->oldTable[i]);
				this->occupancy++;
			}
			this->oldTable[i] = NULL;
		}
	}
	this->oldTable = NULL;
	this->otCapacity = 0;
	this->otOccupancy = 0;
}

int HashTable::tableSize(int table){
	if (table == 1)
		return this->capacity;
	else
		return this->otCapacity;
}

int HashTable::size(int table){
	if (table == 1)
		return this->occupancy;
	else
		return this->otOccupancy;
}

const char * HashTable::at(int index, int table){
	if (table == 0)
		return this->table[index];
	else
		return this->oldTable[index];
}

HashTable::HashTable(int n) {
	this->table = new char*[n];
	this->oldTable = NULL;

	for (int i = 0; i < n; i++) {
		this->table[i] = NULL;
	}

	this->capacity = n;
	this->occupancy = 0;
}

HashTable::~HashTable() {
	if (this->oldTable != NULL) {
		for (int i = 0; i < this->otCapacity; i++) {
			if (this->oldTable[i] != NULL) {
				if (this->oldTable[i] != DELETED)
					free(this->oldTable[i]);
				this->oldTable[i] = NULL;
			}
		}
		delete[] this->oldTable;
	}

	for (int i = 0; i < this->capacity; i++) {
		if (this->table[i] != NULL) {
			if (this->table[i] != DELETED)
				free(this->table[i]);
			this->table[i] = NULL;
		}
	}

	delete[] this->table;
}

char * HashTable::remove(const char *str) {

	int count = 0;
	bool searching = true;
	int index;
	int startIndex;

	if (this->isRehashing()) {
		index = this->hash(str, this->otCapacity);
		startIndex = index;

		// If rehashing, move a cluster
		if (this->isRehashing())
			this->moveCluster(this->hash(str, this->otCapacity));

		while (searching) {
			//check for rehash
			this->rehash(index, count, str);

			//if oldtable is now null thanks to emergency rehash, 
			//pop out of loop since everything is now in the original table
			if (this->oldTable == NULL)
				break;

			// Found string
			if (this->oldTable[index] == NULL || index == startIndex)
				searching = false;

			// Found empty spot or hit last spot to check 
			else if ((this->oldTable[index] != DELETED) && (strcmp(this->oldTable[index], str) == 0)) {
				char* copyString = this->oldTable[index];
				free(this->oldTable[index]);
				this->oldTable[index] = DELETED;
				this->otOccupancy--;
				return copyString;
			}

			// Move to next index
			else
				index++;

			// If index exceeds array size, loop back top 0
			if (index == this->otCapacity)
				index = 0;
		}
	}

	count = 0;
	searching = true;
	index = this->hash(str, this->capacity);
	startIndex = index != 0 ? index - 1 : this->capacity - 1;

	while (searching) {
		this->rehash(index, count, str);
		// Found empty spot or hit last spot to check
		if (this->table[index] == NULL || index == startIndex)
			searching = false;

		// Found string

		else if ((this->table[index] != DELETED) && (strcmp(this->table[index], str) == 0)) {
			char* copyString = this->table[index];
			free(this->table[index]);
			this->table[index] = DELETED;
			this->occupancy--;
			return copyString;
		}

		// Move to next index
		else
			index++;

		// If index exceeds array size, loop back top 0
		if (index == this->capacity)
			index = 0;

		count++;
	}

	// Didn't find anything, return false
	return NULL;
}

bool HashTable::find(const char *str) {
	int count = 0;
	bool searching = true;
	int index;
	int startIndex;

	if (this->isRehashing()) {
		index = this->hash(str, this->otCapacity);
		startIndex = index == 0 ? this->otCapacity : index - 1;

		// If rehashing, move a cluster
		this->moveCluster(this->hash(str, this->otCapacity));

		while (searching) {
			//check for rehash
			this->rehash(index, count, str);

			//if oldtable is now null thanks to emergency rehash, 
			//pop out of loop since everything is now in the original table
			if (this->oldTable == NULL) 
				break;

			// Found empty spot or hit last spot to check
			if (this->oldTable[index] == NULL || index == startIndex)
				searching = false;

			// Found string
			else if ((this->oldTable[index] != DELETED) && (strcmp(this->oldTable[index], str) == 0))
				return true;

			// Move to next index
			else
				index++;

			// If index exceeds array size, loop back top 0
			if (index == this->otCapacity)
				index = 0;

			count++;
		}
	}

	count = 0;
	searching = true;
	index = this->hash(str, this->capacity);
	startIndex = index != 0 ? index - 1 : this->capacity - 1;

	while (searching) {
		this->rehash(index, count, str);
		
		// Found empty spot or hit last spot to check
		if (this->table[index] == NULL || index == startIndex)
			searching = false;

		// Found string
		else if ((this->table[index] != DELETED) && (strcmp(this->table[index], str) == 0))
			return true;

		// Move to next index
		else
			index++;

		// If index exceeds array size, loop back top 0
		if (index == this->capacity)
			index = 0;

		count++;
	}

	// Didn't find anything, return false
	return false;
}

void HashTable::insert(const char *str) {
	bool searching = true;
	char* copyString = strdup(str);
	int index = this->hash(str, this->capacity);
	int count = 0;
	int startIndex = 0;

	while (searching) {
		count++;

		// Check for rehash
		this->rehash(index, count, copyString);
		startIndex = index;

		// After checking for rehashing required, insert item
		if (this->table[index] == NULL || this->table[index] == DELETED) {

			this->table[index] = copyString;
			this->occupancy++;
			searching = false;
		}
		// Found the string in the hashtable already do nothing
		else if (strcmp(this->table[index], copyString) == 0) {
			free(copyString);
			searching = false;
		} 
		else {

			index++;

			if (index == startIndex) {
				cout << "Nothing Inserted, capacity reached, no open spots";
				free(copyString);
				searching = false;
			} else if (index >= this->capacity)
				index = 0;

		}
	}

	// After inserting if we are currently rehashing, move a cluster over
	if (this->isRehashing())
		this->moveCluster(this->hash(str, this->otCapacity));
}

unsigned int HashTable::hash(const char *str, int capacity) {
	return hashCode(str) % capacity;
}

unsigned int HashTable::hashCode(const char *str) {
	unsigned int val = 0; 
	const unsigned int thirtyThree = 33; // magic number from textbook 
	int i = 0 ; 
	while (str[i] != '\0') { 
		val = val * thirtyThree + str[i] ; 
		i++ ; 
	} 
	
	return val; 
}

void HashTable::dump() {

	int tableCount = 1;

	if (this->oldTable != NULL) {
		cout << "HashTable #" << tableCount << ": ";
		cout << "size = " << this->otOccupancy;
		cout << ", tableSize =  " << this->otCapacity << endl;
		for (int i = 0; i < this->otCapacity; i++) {
			cout << "H[" << i << "] = ";
			if (this->oldTable[i] != NULL && this->oldTable[i] != DELETED)
				cout << this->oldTable[i] << " (" << this->hash(this->oldTable[i], this->otCapacity) << ")" << endl;
			else if (this->oldTable[i] == DELETED)
				cout << "DELETED" << endl;
			else
				cout << endl;
		}
		tableCount++;
		cout << endl << endl;
	}

	cout << "HashTable #" << tableCount << ": ";
	cout << "size = " << this->occupancy;
	cout << ", tableSize =  " << this->capacity << endl;
	for (int i = 0; i < this->capacity; i++) {
		cout << "H[" << i << "] = ";
		if (this->table[i] != NULL && this->table[i] != DELETED)
			cout << this->table[i] << " (" << this->hash(this->table[i], this->capacity) << ")" << endl;
		else if (this->table[i] == DELETED)
			cout << "DELETED" << endl;
		else
			cout << endl;
	}
}

bool HashTable::isRehashing() {
	if (this->oldTable == NULL)
		return false;
	return true;
}

void HashTable::rehash(int &index, int count, const char *copyString) {
	// If load factor is more than .5 and we have found more than 10 in a row 
	// when attempting to probe, and we are not rehashing currently, begin
	// rehash process.
	if ((this->occupancy / this->capacity > .5 || count >= 10) && (!this->isRehashing())) {
		bool searching = true;
		int primeIndex = 0;
		int newCapacity = 0;

		while (searching && primeIndex < 17959) {
			newCapacity = primes[primeIndex];
			if ((float)(this->occupancy + 1) / (float)newCapacity < .25)
				searching = false;
			primeIndex++;
		}

		this->oldTable = this->table;
		this->otCapacity = this->capacity;
		this->otOccupancy = this->occupancy;

		this->table = new char*[newCapacity];
		this->capacity = newCapacity;
		this->occupancy = 0;
		for (int i = 0; i < newCapacity; i++) {
			this->table[i] = NULL;
		}
		index = this->hash(copyString, this->capacity);
	}
	else if ((this->occupancy / this->capacity > .5 || count >= 10) && (this->isRehashing())) {
		this->emergencyRehash();
		index = this->hash(copyString, this->capacity);
	}

}

void HashTable::moveCluster(int hashedIndex) {
	if (this->oldTable != NULL) {
		int indexToMove = hashedIndex;

		//Check if the occupancy is more or less than 3%, if more only move a cluster
		if (((float) this->otOccupancy / (float) this->otCapacity) >= .03) {
			// For as long as the previous index isn't NULL, move backwards until you find the begining of the cluster
			while (this->oldTable[indexToMove - 1] != NULL) {
				indexToMove--;

				//If we have hit the first item in the array, set the index to the capacity so 
				//indexToMove - 1 = last index in array
				if (indexToMove == 0)
					indexToMove = this->otCapacity;
			}

			// Move cluster until we hit null
			while (this->oldTable[indexToMove] != NULL) {
				//only move the item if it isn't marked as deleted
				if (this->oldTable[indexToMove] != DELETED) {
					this->insertRehash(this->oldTable[indexToMove]);
					this->oldTable[indexToMove] = NULL;
					this->otOccupancy--;
				}
				//advance the index
				indexToMove++;

				//wrap to the front if needed
				if (indexToMove == this->otCapacity)
					indexToMove = 0;
			}
		}
		//Otherwise its lower than 3% so move the entire table
		else {
			//rotate over entire old table
			for (indexToMove = 0; indexToMove < this->otCapacity; indexToMove++) {
				//If the item isn't deleted, and the item isn't null, move it
				if ((this->oldTable[indexToMove] != DELETED) && (this->oldTable[indexToMove] != NULL)){
					this->insertRehash(this->oldTable[indexToMove]);
					this->oldTable[indexToMove] = NULL;
					this->otOccupancy--;
				}
			}
		}

		//Check if the table is current unoccupied, if it is, set it to NULL, reset the capacity and occupancy
		if (this->otOccupancy <= 0) {
			delete[] this->oldTable;

			this->oldTable = NULL;
			this->otCapacity = 0;
			this->otOccupancy = 0;
		}
	}
}

void HashTable::insertRehash(char *str) {
	bool searching = true;
	int index = this->hash(str, this->capacity);
	int count = 0;
	int startIndex = 0;

	while (searching) {
		count++;

		// Check for rehash
		this->rehash(index, count, str);
		startIndex = index;

		// After checking for rehashing required, insert item
		if (this->table[index] == NULL || this->table[index] == DELETED) {

			this->table[index] = str;
			this->occupancy++;
			searching = false;
		}
		// Found the string in the hashtable already do nothing
		else if (strcmp(this->table[index], str) == 0) {
			free(str);
			searching = false;
		}
		else {

			index++;

			if (index == startIndex) {
				cout << "Nothing Inserted, capacity reached, no open spots";
				free(str);
				searching = false;
			}
			else if (index >= this->capacity)
				index = 0;

		}
	}
}

void HashTable::emergencyRehash() {
	// Find new table size
	bool searching = true;
	int primeIndex = 0;
	int newCapacity = 0;

	while (searching && primeIndex < 17959) {
		newCapacity = primes[primeIndex];
		int combinedSize = this->occupancy + this->otOccupancy + 1;
		if ((float)newCapacity / (float)combinedSize > 4.0)
			searching = false;

		primeIndex++;
	}

	// Create temp third table
	char** thirdTable = this->table;
	int thirdCapacity = this->capacity;
	int thirdOccupancy = this->occupancy;


	this->table = new char*[newCapacity];

	for (int i = 0; i < newCapacity; i++) 
		this->table[i] = NULL;
	
	this->capacity = newCapacity;
	this->occupancy = 0;

	int indexToMove;

	//Move third table
	for (indexToMove = 0; indexToMove < thirdCapacity; indexToMove++) {
		//If the item isn't deleted, and the item isn't null, move it
		if ((thirdTable[indexToMove] != DELETED) && (thirdTable[indexToMove] != NULL)) {
			this->insertRehash(thirdTable[indexToMove]);
			thirdTable[indexToMove] = NULL;
			thirdOccupancy--;
		}

		if (thirdOccupancy == 0)
			break;
	}

	//Move Old Table
	for (indexToMove = 0; indexToMove < this->otCapacity; indexToMove++) {
		//If the item isn't deleted, and the item isn't null, move it
		if ((this->oldTable[indexToMove] != DELETED) && (this->oldTable[indexToMove] != NULL)) {
			this->insertRehash(this->oldTable[indexToMove]);
			this->oldTable[indexToMove] = NULL;
			this->otOccupancy--;
		}

		if (this->otOccupancy == 0)
			break;
	}

	delete[] thirdTable;
	delete[] this->oldTable;

	this->oldTable = NULL;
	this->otCapacity = 0;
	this->otOccupancy = 0;
}