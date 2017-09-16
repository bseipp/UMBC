/* pair.cpp*/
#ifndef _PAIR_CPP_
#define _PAIR_CPP_
#include "Pair.h"

//default constructor
template <class T> 
Pair<T>::Pair()
{}

template <class T> 
Pair<T>::Pair(T first, T second)
{
  m_first = first;
  m_second = second;
}

template <class T> 
T Pair<T>::first() const 
{
  return m_first;
}

template <class T> 
T Pair<T>::second() const
{
  return m_second;
}

template <class T> 
bool Pair<T>::operator== (const Pair<T>& rhs) const {
  if ( m_first == rhs.first() && m_second == rhs.second() )
    return true;
  else if (m_first == rhs.second() && m_second == rhs.first() )
    return true;
  
  return false;
}

#endif
