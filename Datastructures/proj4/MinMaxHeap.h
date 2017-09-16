// File: MinMaxHeap.h
//
// CMSC 341 Spring 2017
//
// Header file for LazyBST class
//

#ifndef _MINMAXHEAP_H_
#define _MINMAXHEAP_H_

#include <stdexcept>   // for throwing out_of_range exceptions
#include <string>
#include <utility>     // for pair template

template<class T> 
class MinMaxHeap {

	class Heap;
	class Node;

public:
	MinMaxHeap(int capacity);

	MinMaxHeap(const MinMaxHeap<T>& other);

	const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);

	~MinMaxHeap();

	void dump();

	void insert(const T& newValue);

	int size();

	T deleteMin();

	T deleteMax();

	void locateMin(int pos, T& data, int& index);

	void locateMax(int pos, T& data, int& index);


private:
	int capacity;
	Heap* minHeap;
	Heap* maxHeap;
};

template<class T>
class MinMaxHeap<T>::Heap {
	friend class MinMaxHeap<T>;

public:
	Heap(int capacity);
	~Heap();

private:
	int size;
	int capacity;
	//compare function
	int(*compare)(T, T);

	Node** heap;
	// Ptr to twins heap
	Heap* twinPtr;

	void addNodeAtIndex(int index, T value);

	int percolateUp();

	void percolateDown(int nodeToBubble);

	void setTwin(Heap* twin);

	void setCompare(int(*fptr)(T, T));

	int insert(const T& newValue);

	void updateTwinIndex(int newIndex);

};

template<class T>
class MinMaxHeap<T>::Node {

	friend class Heap;
	friend class MinMaxHeap<T>;

public:

	Node(T value);

private:

	int twinIndex;
	T value;
};

template<class T>
int compareMin(T lhs, T rhs);

template<class T>
int compareMax(T lhs, T rhs);

#include "MinMaxHeap.cpp"
#endif
