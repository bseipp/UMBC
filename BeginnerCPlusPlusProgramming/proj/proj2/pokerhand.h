/* File: pokerhand.h

   CMSC 202 Computer Science II
   Spring 2016 Project 2

   Class definition of PokerHand Class

   *** YOU MAY ADD PRIVATE HELPER FUNCTIONS ***
   *** DO NOT CHANGE OTHER PARTS OF THIS FILE ***
   */

#ifndef _POKERHAND_H_
#define _POKERHAND_H_

#include "card.h"


class PokerHand {

 public:

  // Avoiding magic numbers.
  // Note: must use PokerHand::FIVE outside member functions.
  //
  static const int FIVE = 5 ;


  // All possible ranks in poker in an enumeration type.
  //
  // A rank of NoRank indicates that the hand is not valid
  // or that the hand has not been evaluated.
  //
  // Note: outside member functions must use refer to this type
  // PokerHand::pRank and use constants PokerHand::RoyalFlush ...
  //
  typedef enum { NoRank, HighCard, OnePair, TwoPair, ThreeOfAKind,
		 Straight, Flush, FullHouse, FourOfAKind, StraightFlush,
		 RoyalFlush } pRank ;


  // Default constructor.
  //
  // We allow a blank PokerHand to be created.
  // However, the default constructor should make sure
  // that m_valid is false and m_rank is NoRank.
  //
  PokerHand() ;


  // Alternate constructor.
  //
  // The alternate constructor should store the FIVE cards
  // given as parameters in the m_cards[] array.
  // It should also immediately evaluate the hand, determine
  // its rank and compute the additonal information (see below).
  //
  // Note: this constructor does not check for validity between
  // cards. For example, the hand created might have two Queen
  // of Hearts.
  //
  PokerHand(Card c0, Card c1, Card c2, Card c3, Card c4) ;


  // Compare the host hand versus otherHand according
  // to the rules of poker. 
  // 
  // Returns a negative number (< 0) 
  // if host hand loses to // the otherHand.
  //
  // Returns a positive number (> 0) 
  // if the host hand beats the otherHand.
  //
  // Returns zero if it's a tie.
  //
  // An invalid hand loses to any hand. If both hands
  // are invalid, the result is undefined (could be
  // negative, zero or positive).
  //
  // Note: the cmp() should not assume that the two hands
  // come from the same deck of cards. E.g., both hands
  // may have 4 Aces, the fifth card should be used to 
  // determine which hand wins.
  //
  int cmp(PokerHand &otherHand) ;


  // Prints out the rank to standard output.
  //
  void printRank() ;


  // Prints out the FIVE cards to standard output
  // one card per line.
  //
  void printCards() ;


  // Return the rank of this hand.
  // If hand is not valid, should return NoRank.
  // Should use rank stored in m_rank, if available.
  // 
  pRank getRank() ;


  // The following "isRank()" functions should all:
  // 1. Assume that the hand is already sorted.
  // 2. If true, store the rank in m_rank.
  // 3. If true, store the "additional information" 
  //    for that rank,
  // 4. Use the rank if m_rank, if available.


  // Returns true if the hand is a Royal Flush.
  //
  bool isRoyalFlush() ;

   
  // Returns true if the hand is a Straight Flush.
  //
  bool isStraightFlush() ;

 
  // Returns true if the hand is Four of a Kind.
  // Sets m_lastCardPoints.
  //
  bool isFourOfAKind() ;


  // Returns true if the hand is a Full House.
  // Sets m_tripletPoints and m_firstPairPoints.
  //
  bool isFullHouse() ;


  // Returns true if the hand is a Flush.
  //
  bool isFlush() ;


  // Returns true if the hand is a Straight.
  //
  bool isStraight() ;


  // Returns true if the hand is Three of a Kind.
  // Sets m_tripletPonts.
  //
  bool isThreeOfAKind() ;


  // Returns true if the hand is a Two Pair.
  // Sets m_firstPairPoints, m_secondPairPoints and
  // m_lastCardPoints.
  //
  bool isTwoPair() ;


  // Returns true if the hand is a One Pair.
  // Sets m_firstPairPoints.
  //
  bool isOnePair() ;


  // Returns true if the hand is High Card.
  // (This means it isn't anything else.)
  //
  bool isHighCard() ;



 private:

  Card m_cards[FIVE] ;   // holds the FIVE cards in this poker hand
  bool m_valid ;         // false if no cards assigned
  pRank m_rank ;         // stored rank


  // The data members below hold some additional information 
  // for this hand that must be computed by evaluate().
  // This information makes it possible to compare two
  // hands when the ranks are equal. For example, if both
  // hands are Two Pair, use m_firstPairPoints to see which
  // hand has higher points for the top pair. If that's a tie,
  // check m_secondPairPoints. If that is also a tie, then
  // use m_lastCardPoints.
  //


  // For Two Pair and Four of a Kind, the point value of the 
  // last card
  //
  Card::cPoints m_lastCardPoints ;    


  // For One Pair, the point value of the pair.   
  // For Two Pair, the point value of the higher pair.
  // For Full House, the point value of the pair.
  //
  Card::cPoints m_firstPairPoints ;


  // For Two Pair, the point value of the lower pair.
  //
  Card::cPoints m_secondPairPoints ;


  // For Full House and Three of a Kind, the point value
  // of the triple.
  //
  Card::cPoints m_tripletPoints ;


  // For Four of a Kind, the point value of the four.
  //
  Card::cPoints m_quadrupletPoints ;


  // Sort the hand by point value. 
  // The cards'suits are not considered in the sort.
  //
  void sort() ;


  // Some helper functions
  // These helper functions assume that the
  // hand is already sorted.


  // Returns true if the cards in the hand
  // have the same suit. Note that this is
  // not the same as isFlush(). This function
  // returns true if the hand is a Flush or
  // a Straight Flush or a Royal Flush. 
  // OTOH, isFlush() returns false if the 
  // hand is a Straight Flush.
  //
  bool isAllOneSuit() ;


  // Returns true if the hand is five cards
  // in an sequence (e.g., 7 8 9 10 Jack).
  // Ace is always 14 and never 1.
  // Note: this is not the same as isStraight()
  // since isStraight() returns false when
  // the hand is a Straight Flush.
  //
  bool isSequence() ;
   

  // End of helper functions


  // -----------------------------------------
  // IF YOU WANT TO ADD MORE HELPER FUNCTIONS,
  // PUT THEIR DECLARATIONS AFTER THIS LINE.
  // -----------------------------------------
  void setRank() ;


} ;


#endif
