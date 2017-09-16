#ifndef _MINMAXHEAP_CPP_
#define _MINMAXHEAP_CPP_

#include "MinMaxHeap.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

template<class T>
MinMaxHeap<T>::MinMaxHeap(int capacity) {
	this->capacity = capacity;
	this->minHeap = new Heap(capacity);
	this->maxHeap = new Heap(capacity);

	this->minHeap->setTwin(this->maxHeap);
	this->minHeap->setCompare(&compareMin);

	this->maxHeap->setTwin(this->minHeap);
	this->maxHeap->setCompare(&compareMax);

}

template<class T>
MinMaxHeap<T>::Heap::Heap(int capacity) {
	//array of node pointers called heap
	this->capacity = capacity;
	this->size = 0;
	this->heap = new Node*[capacity];
	this->twinPtr = NULL;
}

template<class T>
MinMaxHeap<T>::Heap::~Heap() {
	for (int i = 1; i <= this->size; i++) {
		Node* temp =  this->heap[i];
		delete temp;
	}
	delete[] this->heap;
}

template <typename T>
MinMaxHeap<T>::~MinMaxHeap() {
	delete this->minHeap;
	delete this->maxHeap;
}

template <typename T> 
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap& other) {
	this->capacity = other.capacity;
	this->minHeap = new Heap(this->capacity);
	this->maxHeap = new Heap(this->capacity);

	this->minHeap->setTwin(this->maxHeap);
	this->minHeap->setCompare(&compareMin);

	this->maxHeap->setTwin(this->minHeap);
	this->maxHeap->setCompare(&compareMax);

	for (int i = 1; i <= other.minHeap->size; i++) {
		this->minHeap->size++;
		this->maxHeap->size++;

		T value = other.minHeap->heap[i]->value;
		int minHeapIndex = i;
		int maxHeapIndex = other.minHeap->heap[i]->twinIndex;

		this->minHeap->addNodeAtIndex(minHeapIndex, value);
		this->maxHeap->addNodeAtIndex(maxHeapIndex, value);

		this->minHeap->heap[minHeapIndex]->twinIndex = maxHeapIndex;
		this->maxHeap->heap[maxHeapIndex]->twinIndex = minHeapIndex;
	}
}

template <typename T> 
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap& rhs) {
	delete this->minHeap;
	delete this->maxHeap;

	this->capacity = rhs.capacity;
	this->minHeap = new Heap(this->capacity);
	this->maxHeap = new Heap(this->capacity);

	this->minHeap->setTwin(this->maxHeap);
	this->minHeap->setCompare(&compareMin);

	this->maxHeap->setTwin(this->minHeap);
	this->maxHeap->setCompare(&compareMax);

	for (int i = 1; i <= rhs.minHeap->size; i++) {
		this->minHeap->size++;
		this->maxHeap->size++;

		T value = rhs.minHeap->heap[i]->value;
		int minHeapIndex = i;
		int maxHeapIndex = rhs.minHeap->heap[i]->twinIndex;

		this->minHeap->addNodeAtIndex(minHeapIndex, value);
		this->maxHeap->addNodeAtIndex(maxHeapIndex, value);

		this->minHeap->heap[minHeapIndex]->twinIndex = maxHeapIndex;
		this->maxHeap->heap[maxHeapIndex]->twinIndex = minHeapIndex;
	}

	return *this;
}

template<class T>
void MinMaxHeap<T>::Heap::addNodeAtIndex(int index, T value) {
	Node * newNode = new Node(value);

	this->heap[index] = newNode;
}

template<class T>
MinMaxHeap<T>::Node::Node(T value) {
	this->twinIndex = 0;
	this->value = value;
}

template<class T>
void MinMaxHeap<T>::Heap::setTwin(Heap* twin){
	this->twinPtr = twin;
}

template<class T>
void MinMaxHeap<T>::Heap::setCompare(int(*compare)(T, T)) {
	this->compare = compare;
}

template<class T>
int MinMaxHeap<T>::Heap::percolateUp(){
	//store last node for later
	Node * temp = this->heap[this->size];

	int nodeToBubble = this->size;

	for (; nodeToBubble > 1 && 0 > this->compare(temp->value, this->heap[nodeToBubble / 2]->value); nodeToBubble /= 2){
		this->heap[nodeToBubble] = this->heap[nodeToBubble/2];
		//update its twin to the correct position
		this->updateTwinIndex(nodeToBubble);
	}

	this->heap[nodeToBubble] = temp;
	return nodeToBubble;
}

template<class T>
void MinMaxHeap<T>::Heap::percolateDown(int nodeToBubble) {
	//store last node for later
	int child;
	Node * temp = this->heap[nodeToBubble];

	for (; nodeToBubble * 2 <= this->size; nodeToBubble = child) {
		child = nodeToBubble * 2;

		if (child != this->size && 0 > this->compare(this->heap[child + 1]->value, this->heap[child]->value))
			child++;

		if (0 < this->compare(temp->value, this->heap[child]->value)) {
			this->heap[nodeToBubble] = this->heap[child];
			this->updateTwinIndex(nodeToBubble);
		}
		else
			break;
	}

	this->heap[nodeToBubble] = temp;
	this->updateTwinIndex(nodeToBubble);

}

template<class T>
int MinMaxHeap<T>::size() {
	return this->minHeap->size;
}

template<class T>
T MinMaxHeap<T>::deleteMin() {
	if (this->minHeap->size == 0)
		throw std::out_of_range("Heap is empty");

	Node * tempMin = this->minHeap->heap[1];
	Node * tempMax = this->maxHeap->heap[tempMin->twinIndex];

	this->minHeap->heap[1] = this->minHeap->heap[this->minHeap->size];
	this->maxHeap->heap[tempMin->twinIndex] = this->maxHeap->heap[this->maxHeap->size];

	this->minHeap->size--;
	this->maxHeap->size--;

	this->minHeap->percolateDown(1);
	this->maxHeap->percolateDown(tempMin->twinIndex);

	T returnValue = tempMin->value;

	delete tempMin;
	delete tempMax;

	return returnValue;
}

template<class T>
T MinMaxHeap<T>::deleteMax() {
	if (this->maxHeap->size == 0)
		throw std::out_of_range("Heap is empty");

	Node * tempMax = this->maxHeap->heap[1];
	Node * tempMin = this->minHeap->heap[tempMax->twinIndex];

	Node * temp = this->maxHeap->heap[1];

	this->maxHeap->heap[1] = this->maxHeap->heap[this->maxHeap->size];
	this->minHeap->heap[tempMax->twinIndex] = this->minHeap->heap[this->minHeap->size];

	this->maxHeap->size--;
	this->minHeap->size--;

	this->maxHeap->percolateDown(1);
	this->minHeap->percolateDown(tempMax->twinIndex);

	T returnValue = tempMax->value;

	delete tempMin;
	delete tempMax;

	return returnValue;
}

template<class T>
void MinMaxHeap<T>::insert(const T& newValue) {
	if (this->minHeap->size == this->capacity)
		throw std::out_of_range("Capacity exceeded");

	this->minHeap->size++;
	this->maxHeap->size++;
	int minIndex = this->minHeap->insert(newValue);
	int maxIndex = this->maxHeap->insert(newValue);

	this->minHeap->heap[minIndex]->twinIndex = maxIndex;
	this->maxHeap->heap[maxIndex]->twinIndex = minIndex;
}

//function returns the index this was inserted to, after sticking this on the end
template<class T>
int MinMaxHeap<T>::Heap::insert(const T& newValue){
	Node* newNode = new Node(newValue);

	this->heap[this->size] = newNode;

	return this->percolateUp();
}

template<class T>
void MinMaxHeap<T>::Heap::updateTwinIndex(int newIndex) {
	this->twinPtr->heap[this->heap[newIndex]->twinIndex]->twinIndex = newIndex;
}

template<class T>
void MinMaxHeap<T>::dump() {
	cout << "------------Min Heap------------" << endl;
	cout << "size = " << this->minHeap->size << ", capacity = " << this->minHeap->capacity << endl;
	for (int i = 1; i <= this->minHeap->size; i++) 
		cout << "Heap[" << i << "] = (" << this->minHeap->heap[i]->value << "," << this->minHeap->heap[i]->twinIndex << ")" << endl;
	
	cout << "------------Max Heap------------" << endl;
	cout << "size = " << this->maxHeap->size << ", capacity = " << this->maxHeap->capacity << endl;
	for (int i = 1; i <= this->maxHeap->size; i++)
		cout << "Heap[" << i << "] = (" << this->maxHeap->heap[i]->value << "," << this->maxHeap->heap[i]->twinIndex << ")" << endl;
	cout << "--------------------------------" << endl;

}

template<class T>
int compareMin(T lhs, T rhs) {
	//this function will check if the lhs is smaller than the rhs if so its true, otherwise false
	if (lhs < rhs)
		return -1;
	else if (lhs > rhs)
		return 1;
	else
		return 0;
}

template<class T>
int compareMax(T lhs, T rhs) {
	//this function will check if the lhs is smaller than the rhs if so its true, otherwise false
	if (lhs > rhs)
		return -1;
	else if (lhs < rhs)
		return 1;
	else
		return 0;
}

template<class T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index) {
	data = this->minHeap->heap[pos]->value;
	index = this->minHeap->heap[pos]->twinIndex;
}

template<class T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index) {
	data = this->maxHeap->heap[pos]->value;
	index = this->maxHeap->heap[pos]->twinIndex;
}

#endif
