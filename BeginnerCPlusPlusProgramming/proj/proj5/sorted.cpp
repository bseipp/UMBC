#ifndef SORTED_CPP_
#define SORTED_CPP_

using namespace std;

#include <iostream>
#include <stdexcept>
#include "sorted.h"


//Default constructor
template <class T>
sorted<T>::sorted()
{
  m_length = 0;
  m_capacity = 10;  
  for ( int j = 0; j < m_capacity; j++)
    m_data[j] = NULL; 
}


// Non-default constructor copies data from array to sorted
template <class T>
sorted<T>::sorted( T* data, int len )
{
  for (int i = 0; i < len; i++)
    {
      m_data[i] = data[i];
    }
  m_length = len;
  m_capacity = 2 * len;
}

// Copy constructor
template <class T>
sorted<T>::sorted( const sorted<T>& srtd )
{
  for (int i = 0; i < srtd.m_length; i++)
    {
      m_data[i] = srtd.m_data[i];
    }
  m_length = srtd.m_length;
  m_capacity = srtd.m_capacity;
  
}

// Destructor
template <class T>
sorted<T>::~sorted()
{
  
}

// Overloaded assignment operator
template <class T>
sorted<T> sorted<T>::operator=(const sorted<T>& srtd)
{
  
}

// Return the capacity of the storage array
template <class T>
int sorted<T>::capacity() const
{
  return m_capacity;
}

// Return number of items stored
template <class T>
int sorted<T>::size() const
{
  return m_length;
}

// Return the address of the storage array;
// for use in grading programs
template <class T>
T* sorted<T>::getStorageArray() const
{
  return &m_data[0];
}

// Insert an item in sorted; return iterator to inserted item
template <class T>
typename sorted<T>::const_iterator sorted<T>::insert(T data)
{
    if ( m_length == m_capacity )
    {
      m_capacity = m_capacity * 2 ;
      T* temp = new T[m_capacity];

      for ( int i = 0; i < m_length; i++ )
	{
	  temp[i] = *m_data[i];
	}

      delete [] m_data;
      T* m_data = new T[m_capacity];

      for ( int x = 0; x < m_length; x++ )
	m_data[x] = temp[x];
    }

    // put at the end

    T *newData = new T;
    
    *newData = data;
    
    if (m_length == 0 ) 
      {
	m_data[0] = newData;
      }
    else 
      {
	m_data[m_length] = newData;
      }  


    m_length++ ;
    
    if ( m_length > 1 )
      {
	//sort the array
	for ( int p = 0; p < m_length; p++ ) 
	  {
	    for ( int q = p + 1; q < m_length; q++ )
	      {
		if ( *m_data[p] > *m_data[q] ) 
		  {
		    T* tempData = m_data[p];
		    m_data[p] = m_data[q];
		    m_data[q] = tempData;
		  }// end switch if 
	      }// end q for loop
	  }// end p for loop
      }// end if length > 1
    
    //return iterator;
    const_iterator *itr = new const_iterator(newData);
    return *itr;
  
}//end sorted insert



// Remove an item from sorted; return iterator to next item
// after the erased item
template <class T>
typename sorted<T>::const_iterator sorted<T>::erase(const_iterator itr)
{

  T* end = m_data[m_length];    // one past the end of data
  T* ptr = itr.m_current;        // element to erase

  // to erase element at ptr, shift elements from ptr+1 to 
  // the end of the array down one position
  while ( ptr+1 != end ) {
    *ptr = *(ptr+1);
    ptr++;
  }
  
  m_length--;

//erase old element

  if ( (m_length) <= (m_capacity / 4) )
    {
      m_capacity = m_capacity / 4;
      T* temp = new T[m_capacity];

      for ( int i = 0; i < m_length; i++ )
	{
	  temp[i] = *m_data[i];
	}

      delete [] m_data;
      T* m_data = new T[m_capacity];

      for ( int x = 0; x < m_length; x++ )
	m_data[x] = temp[x];
    }// end if

  return itr;
}

// Get element at indx position                                              
template <class T>
const T& sorted<T>::at(int indx)
{
  return *m_data[indx];
}

// Starting iterator value for const_iterator
template <class T>
typename sorted<T>::const_iterator sorted<T>::begin()
{
  const_iterator *itr = new const_iterator(m_data[0]);
  return *itr;
}

// Ending iterator value for const_iterator; typically,
// one element beyond the last valid element in the array
template <class T>
typename sorted<T>::const_iterator sorted<T>::end()
{
  const_iterator *itr = new const_iterator(m_data[m_length]);
  return *itr;
}

// Starting iterator value for rand_iterator.  Should use constant
// value or time(NULL) as seed value for srand().
template <class T>
typename sorted<T>::rand_iterator sorted<T>::rndbegin()
{
  
}


// Starting iterator value for rand_iterator with seed for
// srand() specified.  Given a sorted<T> object x, repeated 
// use of rndbegin( unsigned seed ) with the same seed value
// must produce the same permutation of the elements of x.
template <class T>
typename sorted<T>::rand_iterator sorted<T>::rndbegin( unsigned seed )
{
  return rand_iterator(this, seed) ;
}

// Ending iterator value for rand_iterator
template <class T>
typename sorted<T>::rand_iterator sorted<T>::rndend()
{
  
}



/***********************************************************************/
/*                                                                     */
/*                                                                     */
/*                            Const Iterator                           */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/



// Default constructor
template <class T>
sorted<T>::const_iterator::const_iterator() : m_current(NULL)
{ 
}

// Non-default constructor sets value to given address
template <class T>
sorted<T>::const_iterator::const_iterator(T* addr) : m_current(addr)
{
}

// Pre-increment, e.g. ++itr
template <class T>
typename sorted<T>::const_iterator sorted<T>::const_iterator::operator++()
{
  ++m_current; 
  return *this;
}


// Post-increment, e.g. itr++
template <class T>
typename sorted<T>::const_iterator sorted<T>::const_iterator::operator++(int)
{
  const_iterator result(*this);
  ++(*this);
  return result;
}

// operator!= needed for loop control, e.g. itr != x.end()
template <class T>
bool sorted<T>::const_iterator::operator!=(const const_iterator& itr)
{
  return m_current != itr.m_current;  
}


// Unary dereference operator; returns element currently pointed
// to by the const_iterator
template <class T>
const T& sorted<T>::const_iterator::operator*()
{
  return *m_current;
}


/***********************************************************************/
/*                                                                     */
/*                                                                     */
/*                            Random Iterator                          */
/*                                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

template <class T>
sorted<T>::rand_iterator::rand_iterator()
{
  
}

// Non-default constructor; pointer to sorted<T> object passed 
// as a parameter, which allows the rand_iterator to access 
// variables of the associated sorted<T>> container
template <class T>
sorted<T>::rand_iterator::rand_iterator( sorted<T>* srtdPtr )
{

}

// Non-default constructor; pointer to sorted<T> passed as in
// previous constructor, but also passes seed for random number
// generator
template <class T>
sorted<T>::rand_iterator::rand_iterator( sorted<T>* srtdPtr, unsigned seed )
{

}

// Copy constructor
template <class T>
sorted<T>::rand_iterator::rand_iterator( const rand_iterator& itr )
{

}


// Destructor
template <class T>
sorted<T>::rand_iterator::~rand_iterator()
{

}


// pre-increment
template <class T>
typename sorted<T>::rand_iterator sorted<T>::rand_iterator::operator++()
{

}


// post-increment
template <class T>
typename sorted<T>::rand_iterator sorted<T>::rand_iterator::operator++(int)
{
  
}

// operator!= needed for loop control, e.g. itr != x.end()
template <class T>
bool sorted<T>::rand_iterator::operator!=(const rand_iterator& itr)
{
  return true;
}


// Unary dereference operator
template <class T>
const T& sorted<T>::rand_iterator::operator*()
{
  
}

// Overloaded assignment operator
template <class T>
typename sorted<T>::rand_iterator sorted<T>::rand_iterator::operator=(const rand_iterator& itr)
{

}

#endif
