/* File: CrunoReverse.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the class declarations for the Card class.

*/


#ifndef _CRUNOREVERSE_H_
#define _CRUNOREVERSE_H_

using namespace std;

#include "card.h"

class Game ;
class Player ;

class CrunoReverse : public Card{

public:
  static const unsigned int Reverse = 16 ;

  CrunoReverse(unsigned int s, unsigned int p);
   
  virtual void playCard(Game *gptr, Player *pptr) ;

  virtual string toString() ;
} ;

#endif
