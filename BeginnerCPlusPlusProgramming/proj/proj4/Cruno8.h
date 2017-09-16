/* File: Cruno8.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the class declarations for the Card class.

*/


#ifndef _CRUNO8_H_
#define _CRUNO8_H_

using namespace std;

#include "card.h"

class Game ;
class Player ;

class Cruno8 : public Card{

public:
  Cruno8(unsigned int s, unsigned int p);

  virtual bool playable(Game *gptr) ;
   
  virtual void playCard(Game *gptr, Player *pptr) ;
  
  string suitString(unsigned int cSuit) ;

} ;

#endif
