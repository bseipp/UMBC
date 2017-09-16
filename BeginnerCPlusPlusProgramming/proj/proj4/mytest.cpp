/* File: mytest.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   Sample main program.

*/

#include <iostream>
using namespace std ;

#include "CrunoPlayer.h"
#include "CrunoSkip.h"
#include "CrunoGame.h"
#include "CrunoDraw2.h"
#include "CrunoReverse.h"
#include "Cruno8.h"
#include "card.h"
#include "game.h"
#include "player.h"

int main() {

  // Game One
  // Tests:
  //  - One Deck Game
  //  - Draw Two Card
  //  - Eights Wild Card 
  //  - Skip Card
  CrunoGame G ;

  G.initialize(4) ;  // say we'll have four players

  int n = G.getNumCards() ;

  Player *pptr1 = new CrunoPlayer(&G,n) ;
  Player *pptr2 = new CrunoPlayer(&G,n) ;
  Player *pptr3 = new CrunoPlayer(&G,n) ;
  Player *pptr4 = new CrunoPlayer(&G,n) ;
  G.addPlayer(pptr1) ;
  G.addPlayer(pptr2) ;
  G.addPlayer(pptr3) ;
  G.addPlayer(pptr4) ;

  G.startGame(5545) ;



  
  // Game Two
  // Tests:
  //  - Two Deck Game
  //  - Reverse Card
  //  - Shuffle deck
  CrunoGame G2 ;

  G2.initialize(4) ;  // say we'll have four players

  n = G2.getNumCards() ;

  Player *pptr11 = new CrunoPlayer(&G,n) ;
  Player *pptr22 = new CrunoPlayer(&G,n) ;
  Player *pptr33 = new CrunoPlayer(&G,n) ;
  Player *pptr44 = new CrunoPlayer(&G,n) ;
  G2.addPlayer(pptr11) ;
  G2.addPlayer(pptr22) ;
  G2.addPlayer(pptr33) ;
  G2.addPlayer(pptr44) ;

  G2.startGame(5554) ;

  return 0 ;
}
