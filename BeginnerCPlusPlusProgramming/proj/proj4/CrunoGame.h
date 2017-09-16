/* File: CrunoGame.h

   CMSC 202 Computer Science II
   Spring 2014 Project 4

   This file has the class declarations for the Game class.

*/


#ifndef _CrunoGame_H_
#define _CrunoGame_H_

class Card ;
class Player ;

#include "game.h"

class CrunoGame : public Game{

 public:
  void drawTwo();

  virtual Card * dealOneCard();
  
  virtual unsigned int nextPlayer();
  
  virtual unsigned int playerAfter(unsigned int thisPlayer);

  virtual ~CrunoGame();

  virtual void initialize(int numPlayers) ;

  bool nextPlayerLess();

  void changeDirection();

  int m_direction;

} ;

#endif
