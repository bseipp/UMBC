

/* File: CrunoGame.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the implemenation of the Game class.

*/


#include <stdlib.h>
#include <iostream>
using namespace std ;

#include "CrunoDraw2.h"
#include "CrunoSkip.h"
#include "CrunoGame.h"
#include "player.h"
#include "game.h"
#include "card.h"
#include "Cruno8.h"
#include "CrunoReverse.h"
#include "CrunoPlayer.h"

CrunoGame::~CrunoGame()
{}

static void ifNullCrash(void *ptr) {
   if (ptr == NULL) {
      cerr << "Could not allocate memory\n" ;
      exit(1) ;
   }
   return ;
}

// Initialize the game based on the number of players.
//
void CrunoGame::initialize(int numPlayers) {
   m_suit = 0 ;
   m_points = 0 ;
   m_currentPlayer = 0 ;
   m_direction = 1;

   // can't play by yourself
   //
   if (numPlayers < 2) {
      cerr << "Insufficient players\n" ;
      exit(1) ;
   }

   // not enough cards to make it fun for >10.
   //
   if (numPlayers > 10) {
      cerr << "Too many players\n" ;
      exit(1) ;
   }

   m_numPlayers = 0 ;  // no players added yet.

   // allocate space for max requested
   //
   m_maxPlayers = numPlayers ;
   m_players = new Player*[numPlayers] ;
   ifNullCrash(m_players) ;

   m_winner = m_maxPlayers + 1 ;  // not a real player

   // usually use just one deck
   int decks = 1 ;
   m_maxCards = 76 ;   // 52 cards in one deck

   if (numPlayers > 5) {
      // use two decks
      decks = 2 ;
      m_maxCards = 152 ;   // 104 cards in two decks
   }


   // allocate space for the discard pile
   m_discard = new Card*[m_maxCards] ;
   ifNullCrash(m_discard) ;
   m_numDiscard = 0 ;  // nothing discarded yet

   // allocate space for the stock pile
   m_stock = new Card*[m_maxCards] ;
   ifNullCrash(m_stock) ;


   int i = 0 ;  // next available slot in m_stock[]

   for (int d = 0 ; d < decks ; d++) {  // # of decks
      
      // iterate over suits
      for (unsigned int s = Card::Clubs ; s <= Card::Spades ; s++) {

         // iterate over point values 
	for (unsigned int p = 2 ; p <= CrunoDraw2::DrawTwo ; p++) {
	   if ( p == 8 )
	     {
	       m_stock[i] = new Cruno8(s,p) ;  // insert new cruno8 card
	       ifNullCrash(m_stock[i]) ;
	       i++ ;
	     }

	   else if ( p == CrunoSkip::Skip )
	     {
	       //add first skip
	       m_stock[i] = new CrunoSkip(s,p) ;
	       ifNullCrash(m_stock[i]) ;
	       i++;
	       //add second skip
	       m_stock[i] = new CrunoSkip(s,p) ;
	       ifNullCrash(m_stock[i]) ;
	       i++;
	     }

	   else if ( p == CrunoReverse::Reverse )
	     {
	       //add first reverse
	       m_stock[i] = new CrunoReverse(s,p) ;
	       ifNullCrash(m_stock[i]) ;
	       i++;

	       //add second reverse
	       m_stock[i] = new CrunoReverse(s,p) ;
	       ifNullCrash(m_stock[i]) ;
	       i++;
	     }

	   else if ( p == CrunoDraw2::DrawTwo )
	     {

	       //add first draw 2
	       m_stock[i] = new CrunoDraw2(s,p) ;
	       ifNullCrash(m_stock[i]) ;
	       i++;

	       //add second draw 2
	       m_stock[i] = new CrunoDraw2(s,p) ;
	       ifNullCrash(m_stock[i]) ;
	       i++;	       
	     }
	   else
	     {
	       m_stock[i] = new Card(s,p) ;  // insert new card
	       ifNullCrash(m_stock[i]) ;
	       i++ ;
	     }
	}
      }
   }

   // remember how many cards we added
   m_numStock = m_maxCards ;

   // Still haven't started (need to have players added)
   m_started = false ;
   m_over = false ;
}

unsigned int CrunoGame::nextPlayer() {
  m_currentPlayer = (m_currentPlayer + m_direction) % m_numPlayers ;
  return m_currentPlayer ;
}

unsigned int CrunoGame::playerAfter(unsigned int thisPlayer) {
  return (thisPlayer + m_direction) % m_numPlayers ;
}

void CrunoGame::changeDirection()
{
  m_direction = m_direction * -1;
}

void CrunoGame::drawTwo()
{
  Card *cptr;

  cptr = dealOneCard() ;
  int p = playerAfter(currentPlayer()) ;
  if (cptr == NULL) return ;
  cout << "Player " << p << " draws a card: " << cptr->toString() << endl ;
  m_players[p]->takeCard(cptr) ;

  cptr = dealOneCard() ;
  if (cptr == NULL) return ;
  cout << "Player " << p << " draws a second card: " << cptr->toString() << endl ;
  m_players[p]->takeCard(cptr) ;

  return;
}

bool CrunoGame::nextPlayerLess()
{
  int p = currentPlayer();
  int q = playerAfter(p);
  
  CrunoPlayer *currentPlayer ;
  CrunoPlayer *playerAfter;
  currentPlayer = dynamic_cast<CrunoPlayer *>( m_players[p] ) ;
  playerAfter = dynamic_cast<CrunoPlayer *>( m_players[q] ) ;

  if ( currentPlayer -> getNumCards() >= playerAfter -> getNumCards() )
    return true;
  return false;
}

Card *CrunoGame::dealOneCard() {
  Card *cptr ;

  cout << "Cards left in deck: " << m_numStock << endl;

  if (m_numDiscard < 1)
    {
      cout << "No more cards to play! Buy more decks! " << endl << endl;
      m_over = true ;
      return NULL;
    }
  else if (m_numStock < 1) 
    {
      cout << m_numDiscard << endl;
      cout << "Shuffling Cards from discard. " << endl;

      unsigned int i,j;
      m_numStock = m_numDiscard ; 

      Card *tempPile[m_numStock];
 
      for (i = 0; i < m_numStock; i++)
	m_stock[i] = m_discard[i];

      for (i = 0; i < m_numStock; i++)
	m_discard[i] = tempPile[i];

      //shuffle cards
      //
      srand(rand() & 10000000) ;
      for(unsigned int i = 0 ; i < m_numStock ; i++) {
	Card *temp ;
	
	j = rand() % m_numStock ;
	temp = m_stock[i] ;
	m_stock[i] = m_stock[j] ;
	m_stock[j] = temp ;
      }
      m_numDiscard = 1;
    }

  // Gimme!
  //
  m_numStock-- ;
  cptr = m_stock[m_numStock] ;
  m_stock[m_numStock] = NULL ;


  return cptr ;
}
