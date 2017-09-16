#ifndef MYARRAY_CPP
#define MYARRAY_CPP

#include <iostream>
#include <stdexcept>
#include "my_array.h"

using namespace std;

my_array::my_array() { m_size = 0; }

my_array::my_array(int* data, int len) {

  // if data array is too long, throw range_error exception
  if ( len > MAX_SIZE )
    throw range_error("my_array(int* data, int len): len exceeds MAX_SIZE");

  // copy data to m_data
  for (int i = 0; i < len; i++) 
    m_data[i] = data[i];
  m_size = len;
}

int my_array::size() { return m_size; }

const int& my_array::at(unsigned int indx) {
  return m_data[indx];
}

my_array::const_iterator my_array::begin() { 
  return const_iterator(&m_data[0]); 
}

my_array::const_iterator my_array::end() { 
  // return address of element one past the
  // end of the array
  return const_iterator(&m_data[m_size]); 
}

my_array::const_iterator my_array::push_back(int data) {

  // if the array is already full, throw out_of_range exception
  if ( m_size == MAX_SIZE )
    throw out_of_range("my_array::push_back(): MAX_SIZE exceeded");
  else {
    m_size++;
    m_data[m_size-1] = data;
    return const_iterator(&m_data[m_size-1]);
  }
}

my_array::const_iterator my_array::erase(const_iterator itr) {
  int* end = &m_data[MAX_SIZE];    // one past the end of data
  int* ptr = itr.m_current;        // element to erase

  // to erase element at ptr, shift elements from ptr+1 to 
  // the end of the array down one position
  while ( ptr+1 != end ) {
    *ptr = *(ptr+1);
    ptr++;
  }
  
  m_size--;

  return itr;
}

my_array::const_iterator::const_iterator() : m_current(NULL) {}  

my_array::const_iterator::const_iterator(int* addr) : m_current(addr) {}

my_array::const_iterator my_array::const_iterator::operator++() { 
  ++m_current; return *this; 
}

my_array::const_iterator my_array::const_iterator::operator++(int) { 
  const_iterator result(*this);
  ++(*this);
  return result;
}

bool my_array::const_iterator::operator!=(const const_iterator& itr) {
  return m_current != itr.m_current;
}

const int& my_array::const_iterator::operator*() { return *m_current; }

#endif
