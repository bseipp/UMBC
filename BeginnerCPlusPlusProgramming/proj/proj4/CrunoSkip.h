/* File: CrunoSkip.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the class declarations for the Card class.

*/


#ifndef _CRUNOSKIP_H_
#define _CRUNOSKIP_H_

using namespace std;

#include "card.h"

class Game ;
class Player ;

class CrunoSkip : public Card{

public:
  static const unsigned int Skip = 15 ;

  CrunoSkip(unsigned int s, unsigned int p);
   
  virtual void playCard(Game *gptr, Player *pptr) ;

  virtual string toString() ;
} ;

#endif
