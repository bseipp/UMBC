/* File: Cruno8.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the class declarations for the Card class.

*/

#include <iostream>
#include <sstream>
#include <string>

using namespace std ;

#include "player.h"
#include "game.h"
#include "Cruno8.h"
#include "card.h"

bool Cruno8::playable(Game *gptr)
{
  return true;
}

void Cruno8::playCard(Game *gptr, Player *pptr) {
  gptr->setSuit(pptr -> pickSuit()) ;
  gptr->setPoints(m_points) ;
  cout << "Suit is now " << suitString(gptr->currentSuit()) << "." << endl;
  return ;
}

string Cruno8::suitString(unsigned int cSuit)
{
  int suit = cSuit ;
  ostringstream oss ;

  switch ( suit ) {
  case Clubs :
    oss << "Clubs" ;
    break ;
  case Diamonds :
    oss << "Diamonds" ;
    break ;
  case Hearts :
    oss << "Hearts" ;
    break ;
  case Spades :
    oss << "Spades" ;
    break ;
  default :
    oss << "INVALID SUIT\n" ;
  }

  return oss.str();
}

Cruno8::Cruno8(unsigned int suit, unsigned int points) : Card(suit, points) {
  m_points = points;
  m_suit = suit;
}

