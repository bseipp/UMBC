/* File: crunoplayer.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the implementation of the Player class.

*/
#ifndef _CRUNOPLAYER_H_
#define _CRUNOPLAYER_H_

#include "card.h"
#include "game.h"
#include "player.h"

class CrunoPlayer : public Player
{

 public:
  CrunoPlayer(Game *gptr, unsigned int numCards);
  
  virtual ~CrunoPlayer();
  
  virtual unsigned int pickSuit();

  virtual Card *playOneCard(bool &lastCard, bool &oneCardLeft) ;

  int getNumCards();

  unsigned int favoredSuit();

};

#endif
