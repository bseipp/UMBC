#ifndef MYARRAY_H
#define MYARRAY_H

using namespace std;

class my_array {

 public:

  // Size of storage array.  Maximum number of ints that can be
  // stored in a my_array object
  static const int MAX_SIZE = 10;

  // Forward declare iterator classe(s)
  class const_iterator;

  //Default constructor
  my_array();

  // Non-default constructor copies data from array to my_array  
  my_array(int* data, int len);
  
  // Return number of items in my_array
  int size();

  // Append an item to my_array; return iterator to inserted item
  const_iterator push_back(int data);

  // Remove an item from my_array; return iterator to next item
  // after erased item
  const_iterator erase(const_iterator itr);
  
  // Get element at indx position
  const int& at(unsigned int indx);

  // begin() function for use with const_iterator
  const_iterator begin();

  // end() function for use with const_iterator
  const_iterator end();

  // const_iterator is a class within my_array
  class const_iterator {
  public:

    // Allows my_array to access const_iterator's private variables.
    // Used by my_array::erase().
    friend class my_array;

    // Default constructor
    const_iterator();

    // Non-default constructor sets m_current to given address
    const_iterator(int* addr);

    // Pre-increment const_iterator
    const_iterator operator++();

    // Post-increment const_iterator
    const_iterator operator++(int);

    // operator!= needed for loop control, e.g. itr != x.end()
    bool operator!=(const const_iterator& itr);

    // Unary dereference operator 
    const int& operator*();
    
  private:
    int* m_current;  // pointer to current entry in array
  };

 private:
  int m_size;              // number of items in my_array
  int m_data[MAX_SIZE];    // storage array
};

#endif
