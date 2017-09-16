/* File: card.h

   CMSC 202 Computer Science II
   Spring 2016 Project 2

   This file has the class declartions for the Card class.

   *** DO NOT CHANGE THIS FILE ***

*/


#ifndef _CARD_H_
#define _CARD_H_

class Card {

 public:


  // Type definition for the suits of a playing card.
  // Invalid means the host Card has not been initialized.
  //
  // Note: outside Card member functions, use Card::cSuit, 
  // Card::Spades, Card::Hearts, ...
  //
  typedef enum { Invalid, Clubs, Diamonds, Hearts, Spades} cSuit ;


  // Type definition for the point value of a playing card.
  // A point value of 0 means the host Card has not been initialized.
  // Jack = 11, Queen = 12, King = 13, Ace = 14.
  // A point value of 1 is not used.
  // 
  // Note: outside Card member functions, use Card::cPoints
  //
  typedef unsigned int cPoints ;


  // Default constructor.
  //
  // We allow uninitialized Cards to be created.
  // This allows arrays of Cards.
  // Uninitialized cards should have Invalid for its suit
  // and 0 for its points.
  // 
  Card() ; 


  // Alternate constructor.
  //
  // Create a Card with specified suit and points.
  // The alternate constructor should make sure that
  // the values of the arguments are valid.
  // If invalid arguments are given, a Card should
  // created with Invalid for its suit and 0 for its points.
  //
  Card(cSuit s, cPoints p) ;


  // Returns suit of the host Card.
  //
  cSuit suit() ;


  // Returns point value of the host Card.
  //
  cPoints points() ; 


  // Prints a description of the host Card to standard output.
  // The output should look like:
  //   8 of Diamonds
  //   Queen of Hearts
  //   ...
  //
  void print() ;
    

 private:

  cSuit m_suit ;        // suit of host Card
  cPoints m_points ;    // point value of host Card

} ;

#endif
