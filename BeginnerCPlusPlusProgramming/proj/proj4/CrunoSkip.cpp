
/* File: CrunoSkip.cpp

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
#include "card.h"
#include "CrunoSkip.h"



void CrunoSkip::playCard(Game *gptr, Player *pptr) {
  gptr->setSuit(m_suit) ;
  gptr->setPoints(m_points) ;
  cout << "Skipping player " << gptr->playerAfter(gptr->currentPlayer()) << endl;
  gptr->nextPlayer();
  return ;
}

CrunoSkip::CrunoSkip(unsigned int s, unsigned int p) : Card(s, p)
{
  m_points = p;
  m_suit = s;
}

string CrunoSkip::toString() {
  
  ostringstream oss ;
  
  oss << "Skip";
  
  switch ( m_suit ) {
  case Clubs :
    oss << " of Clubs" ;
    break ;
  case Diamonds :
    oss << " of Diamonds" ;
    break ;
  case Hearts :
    oss << " of Hearts" ;
    break ;
  case Spades :
    oss << " of Spades" ;
    break ;
  default :
    oss << "of INVALID SUIT\n" ;
  }
  
  return oss.str() ;
}


