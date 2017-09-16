/* File: CrunoReverse.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the class declarations for the Card class.

*/


#ifndef _CRUNODRAW2_H_
#define _CRUNODRAW2_H_

using namespace std;

#include "card.h"

class Game ;
class Player ;

class CrunoDraw2 : public Card{

public:
  static const unsigned int DrawTwo = 17 ;
  unsigned int p;

  CrunoDraw2(unsigned int s, unsigned int p);
   
  virtual void playCard(Game *gptr, Player *pptr) ;

  virtual string toString() ;
} ;

#endif
