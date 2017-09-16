/* File: CrunoPlayer.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the implementation of the Player class.

*/

#include <stdlib.h>
#include <iostream>

using namespace std ;

#include "card.h"
#include "player.h"
#include "game.h"
#include "CrunoPlayer.h"
#include "CrunoGame.h"
#include "CrunoDraw2.h"

// Create Player and allocate array to store Card pointers.
//
CrunoPlayer::CrunoPlayer(Game *gptr, unsigned int numCards) : Player(gptr, numCards)
{

}

int CrunoPlayer::getNumCards()
{
  return m_numCards;
}

Card *CrunoPlayer::playOneCard(bool &lastCard, bool &oneCardLeft) {

   unsigned int c ;
   Card *cptr, *temp ;
   bool noCardPlayed = true;

   CrunoGame *cgptr ;
   cgptr = dynamic_cast<CrunoGame *>(m_game) ;

   // find first card that is playable
   
   c = 0 ;        // index into array of Card pointers
   cptr = NULL ;  // haven't found a playable card yet

   while( noCardPlayed ) {
      if ( c >= m_numCards ) break ;   // hit end of array

      if ( cgptr -> nextPlayerLess() &&
	   m_cards[c] -> getPoints() == CrunoDraw2::DrawTwo &&
	   m_cards[c] -> playable(m_game) )
	{

	  cptr = m_cards[c] ;  // remember the card

	  // To remove the card we will play from the hand,
	  // we replace it with the last card in the array.
	  // This changes the order of the cards, but
	  // order doesn't matter here.

	  m_numCards-- ;                       // one less card
	  m_cards[c] = m_cards[m_numCards] ;   // replace with last card
	  m_cards[m_numCards] = NULL ;         // just to be safe

	  if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
	  if (m_numCards == 0) lastCard = true ;     // did we win?
	  noCardPlayed = false;
	}
      c++ ;
      
   }// end draw two while loop 

   c = 0 ;

   while ( noCardPlayed ) {
     if ( c >= m_numCards ) break ;

     if ( m_cards[c]->playable(m_game) && 
	  m_cards[c] != NULL &&
	  m_cards[c]->getSuit() == favoredSuit()) { // found playable card
       
       cptr = m_cards[c] ;  // remember the card
       
       // To remove the card we will play from the hand,
       // we replace it with the last card in the array.
       // This changes the order of the cards, but
       // order doesn't matter here.
       
       m_numCards-- ;                       // one less card
       m_cards[c] = m_cards[m_numCards] ;   // replace with last card
       m_cards[m_numCards] = NULL ;         // just to be safe
       
       if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
       if (m_numCards == 0) lastCard = true ;     // did we win?
       
       noCardPlayed = false ;
     }
     c++ ; 
   }

   c = 0;

   while ( noCardPlayed ) {
     if (c >= m_numCards ) break;
     
     if (m_cards[c]->playable(m_game)) { // found playable card
       
       cptr = m_cards[c] ;  // remember the card
       
       // To remove the card we will play from the hand,
       // we replace it with the last card in the array.
       // This changes the order of the cards, but 
       // order doesn't matter here.
       
       m_numCards-- ;                       // one less card
       m_cards[c] = m_cards[m_numCards] ;   // replace with last card
       m_cards[m_numCards] = NULL ;         // just to be safe
       
       if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
       if (m_numCards == 0) lastCard = true ;     // did we win?
       noCardPlayed = false ;
     }
     c++ ;    // no pun intended
   }
   
   return cptr ; 
   
}

unsigned int CrunoPlayer::pickSuit() {
  return favoredSuit();
}

unsigned int CrunoPlayer::favoredSuit()
{
  int heartCount = 0;
  int spadeCount = 0;
  int diamondCount = 0;
  int clubCount = 0;
  unsigned int favoredSuit = 0;

  for (int i = 0; i < m_numCards; i++)
    {
      if (m_cards[i] -> getSuit() == Card::Hearts)
	heartCount++;
      else if (m_cards[i] -> getSuit() == Card::Spades)
	spadeCount++;
      else if (m_cards[i] -> getSuit() == Card::Diamonds)
	diamondCount++;
      else if (m_cards[i] -> getSuit() == Card::Clubs)
	clubCount++;
    }

  if ( heartCount >= spadeCount &&
       heartCount >= diamondCount &&
       heartCount >= clubCount )
    favoredSuit = Card::Hearts;
  else if ( spadeCount >= heartCount &&
	    spadeCount >= diamondCount &&
	    spadeCount >= clubCount )
    favoredSuit = Card::Spades;
  else if ( diamondCount >= heartCount &&
	    diamondCount >= spadeCount &&
	    diamondCount >= clubCount )
    favoredSuit = Card::Diamonds;
  else if ( clubCount >= heartCount &&
	    clubCount >= diamondCount &&
	    clubCount >= spadeCount )
    favoredSuit = Card::Clubs;
  
  return favoredSuit;
}

CrunoPlayer::~CrunoPlayer() {}
