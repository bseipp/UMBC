/* File: card.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 2

   Implementation of Card member functions.
   See card.h for documentation.

*/

#include <iostream>
#include "card.h"

using namespace std ;


// Default constructor marks card as invalid
//
Card::Card() {
  m_suit = Invalid ;
  m_points = 0 ;
}


Card::Card(cSuit s, cPoints p) {

  m_suit = s;
  m_points = p;

}


Card::cPoints Card::points() {

  return m_points;

}

Card::cSuit Card::suit() {

  return m_suit;

}


void Card::print() {
  const string suitType[] = { "Invalid", "Clubs", "Diamonds", "Hearts", "Spades" }; 
  const string pointType[] = { "Invalid", "Invalid", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" }; 
  
  cout << pointType[m_points] << " of " << suitType[(int)m_suit] << endl;

}
