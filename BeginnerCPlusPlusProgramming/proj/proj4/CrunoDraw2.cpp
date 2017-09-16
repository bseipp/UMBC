/* File: CrunoDraw2.cpp

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
#include "CrunoDraw2.h"
#include "CrunoGame.h"

void CrunoDraw2::playCard(Game *gptr, Player *pptr) {
  gptr->setSuit(m_suit) ;
  gptr->setPoints(m_points) ;
  CrunoGame *cgptr;
  cgptr = dynamic_cast<CrunoGame *>(gptr);
  
  cgptr->drawTwo();

  return ;
}

CrunoDraw2::CrunoDraw2(unsigned int s, unsigned int p) : Card(s, p)
{
  m_suit = s;
  m_points = p;
}

string CrunoDraw2::toString() {
  
  ostringstream oss ;
  
  oss << "Draw 2";
  
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


