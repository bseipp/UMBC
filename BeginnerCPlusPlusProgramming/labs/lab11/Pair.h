/* Pair.h */

#ifndef _PAIR_H_
#define _PAIR_H_

template <class T>
class Pair
{
 public: 
  Pair();
  
  Pair(T first, T second);
  
  T first() const;
  
  T second() const;
  
  bool operator== (const Pair& rhs) const;

 private:
  T m_first;
  
  T m_second;

};
#include "Pair.cpp"
#endif

