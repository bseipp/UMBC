// File: HashTable.h
//
// CMSC 341 Spring 2017
//
// Header file for HashTable class
//
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <cstring>
#include <stdexcept>   // for throwing out_of_range exceptions
using namespace std;
class HashTable {
	static char * const DELETED;

public: 
	HashTable(int n = 101);
	HashTable(HashTable& other);
	const HashTable& operator= (HashTable& rhs);
	~HashTable();

	int tableSize(int table = 0); 
	int size(int table = 0); 
	const char * at(int index, int table = 0);	
	void insert(const char *str);
	bool find(const char *str);
	char * remove(const char *str);
	void dump();
	bool isRehashing();

private: 
	char** table;
	char** oldTable;
	int capacity;
	int occupancy;
	int otCapacity;
	int otOccupancy;

	void forceRehash();
	void rehash(int &index, int count, const char *copyString);
	void insertRehash(char *str);
	void moveCluster(int hashedIndex);
	void emergencyRehash();
	unsigned int hashCode(const char *str);
	unsigned int hash(const char *str, int capacity);
};

#endif