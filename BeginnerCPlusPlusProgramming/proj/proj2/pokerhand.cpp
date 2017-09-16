/* File: pokerhand.cpp

   Brian Seipp
   
   Section: 19

   CMSC 202 Computer Science II
   Spring 2016 Project 2
   
   Implementation of PokerHand class.
   See pokerhand.h for documentation.
*/


#include <iostream>
using namespace std ;

#include "pokerhand.h"



/******************************************************************
 *                                                                *
 * Name:          PokerHand (Default Constructor)                 *
 *                                                                *
 * PreCondition:  None                                            *
 *                                                                *
 * PostCondition: - creates a default pokerhand object that       *
 *                  assigns the points of all cards to 0, and     *
 *                  the rank to NoRank, and m_valid to false      *
 *                                                                *
 *****************************************************************/
PokerHand::PokerHand () {
  m_valid = false ;
  m_rank = NoRank ;
  
  m_lastCardPoints = 0 ;
  m_firstPairPoints = 0 ;
  m_secondPairPoints = 0 ;
  m_tripletPoints = 0 ;
  m_quadrupletPoints = 0 ;
}// end default constructor



/******************************************************************
 *                                                                *
 * Name:          PokerHand (Non-Default Constructor)             *
 *                                                                *
 * PreCondition:  - five card objects are used in call, all valid *
 *                                                                *
 * PostCondition: - creates a pokerhand object using the five     * 
 *                  cards used in the call                        *
 *                - sorts the hand                                *
 *                - sets the rank of the hand                     *
 *                                                                *
 *****************************************************************/
PokerHand::PokerHand (Card c0, Card c1, Card c2, Card c3, Card c4) {

  // Store cards
  m_cards[0] = c0 ;
  m_cards[1] = c1 ;
  m_cards[2] = c2 ;
  m_cards[3] = c3 ;
  m_cards[4] = c4 ;


  // We have cards.
  // Note: this assumes c0, ..., c4 are valid
  //
  m_valid = true ;
  m_rank = NoRank ;

  // Default values for "additional information"
  //
  m_lastCardPoints = 0 ;
  m_firstPairPoints = 0 ;
  m_secondPairPoints = 0 ;
  m_tripletPoints = 0 ;
  m_quadrupletPoints = 0 ;

  // Don't forget to sort
  //
  sort() ;


  // IF YOU WANT THE ALTERNATE CONSTRUCTOR
  // TO DO MORE, PLACE THE CODE AFTER THIS
  // LINE:
  // --------------------------------------
  setRank();

}// end constructor


/******************************************************************
 *                                                                *
 * Name:          sort()                                          *
 *                                                                *
 * PreCondition:  pokerhand object has five card objects          *
 *                initialized with points values                  *
 *                Constant FIVE is set to a positive integer      *
 *                                                                *
 * PostCondition: m_cards array is sorted in ascending order of   *
 *                points value                                    *
 *                                                                *
 *****************************************************************/
void PokerHand::sort () {
  //Poker hand is sorted here by ascending order of points
  Card tempCard; //placeholder for the card that is being swapped

  for (int i = 0; i < FIVE; i++) {
    for (int y = i+1; y < FIVE; y++) {
      if (m_cards[i].points() > m_cards[y].points()) {
	tempCard = m_cards[i];
	m_cards[i] = m_cards[y];
	m_cards[y] = tempCard;
     }// end else
    }// end for y
  }// end for i
}// end sort

/******************************************************************
 *                                                                *
 * Name:          printCards                                      *
 *                                                                *
 * PreCondition:  Constant FIVE is set to a positive integer      *
 *                                                                *
 * PostCondition: The cards of the pokerhand object are printed   *
 *                to the screen                                   *
 *                                                                *
 *****************************************************************/
void PokerHand::printCards() {
  cout << endl;
  for (int j = 0; j < FIVE; j++)
    m_cards[j].print();
}//end printCards


/******************************************************************
 *                                                                *
 * Name:          printRank                                       *
 *                                                                *
 * PreCondition:  getRank is valid and returns an enumerated rank *
 *                                                                *
 * PostCondition: prints the rank of a pokerhand in plaintext     *
 *                to the screen                                   *
 *                                                                *
 *****************************************************************/

void PokerHand::printRank() {
  string handRank[] = 
    {"No Rank",
     "High Card",
     "One Pair",
     "Two Pair",
     "Three of a Kind",
     "Straight",
     "Flush",
     "Full House",
     "Four of a Kind",
     "Straight Flush",
     "Royal Flush"};
  cout << handRank[(int)getRank()];
}//end print Rank

/******************************************************************
 *                                                                *
 * Name:          isHighCard()                                    *
 *                                                                *
 * PreCondition:  m_cards is populated with valid card objects    *
 *                                                                *
 * PostCondition: - Always returns true, as this is the lowest    *
 *                  poker hand possible.                          *
 *                - m_lastCardPoints is populated with the highest*
 *                  card value in the hand.                       *
 *                - m_rank is populated as HighCard               *
 *                                                                *
 *****************************************************************/

bool PokerHand::isHighCard() {
  m_lastCardPoints = m_cards[4].points();
  m_rank = HighCard;
  return true;
}//end isHighCard


/******************************************************************
 *                                                                *
 * Name:          isOnePair ()                                    *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - FIVE is a valid integer greater than 0        *
 *                                                                *
 * PostCondition: - returns true if the hand contains a pair.     *
 *                - m_firstPairPoints is populated with the       *
 *                  point value of the pair                       *
 *                - m_rank is populated as OnePair                *
 *                                                                *
 *****************************************************************/
bool PokerHand::isOnePair() {
  //check 2-1-1-1
  if ( m_cards[0].points() == m_cards[1].points() &&
       m_cards[1].points() != m_cards[2].points() &&
       m_cards[2].points() != m_cards[3].points() &&
       m_cards[3].points() != m_cards[4].points() ) {
    m_firstPairPoints = m_cards[0].points();
    m_rank = OnePair;
    return true;
  }// end if

  //check 1-2-1-1
  else if ( m_cards[0].points() != m_cards[1].points() &&
	    m_cards[1].points() == m_cards[2].points() &&
	    m_cards[2].points() != m_cards[3].points() &&
	    m_cards[3].points() != m_cards[4].points() ) {
    m_firstPairPoints = m_cards[1].points();
    m_rank = OnePair;
    return true;
  }// end else if


  //check 1-1-2-1
  else if ( m_cards[0].points() != m_cards[1].points() &&
	    m_cards[1].points() != m_cards[2].points() &&
	    m_cards[2].points() == m_cards[3].points() &&
	    m_cards[3].points() != m_cards[4].points() ) {
    m_firstPairPoints = m_cards[2].points();
    m_rank = OnePair;
    return true;
  }// end else if

  //check 1-1-1-2
  else if ( m_cards[0].points() != m_cards[1].points() &&
	    m_cards[1].points() != m_cards[2].points() &&
	    m_cards[2].points() != m_cards[3].points() &&
	    m_cards[3].points() == m_cards[4].points() ) {
    m_firstPairPoints = m_cards[3].points();
    m_rank = OnePair;
    return true;
  }// end else if

  return false;
}//end isOnePair



/******************************************************************
 *                                                                *
 * Name:          isTwoPair ()                                    *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - FIVE is a valid integer greater than 0        *
 *                                                                *
 * PostCondition: - returns true if the hand contains two pairs   *
 *                - m_firstPairPoints is populated with the       *
 *                  point value of the highest pair               *
 *                - m_rank is populated as TwoPair                *
 *                                                                *
 *****************************************************************/
bool PokerHand::isTwoPair() {
  //check 2-2-1
  if ( m_cards[0].points() == m_cards[1].points() &&
       m_cards[1].points() != m_cards[2].points() &&
       m_cards[2].points() == m_cards[3].points() &&
       m_cards[3].points() != m_cards[4].points() ) {
    m_firstPairPoints = m_cards[0].points();
    m_secondPairPoints = m_cards[2].points();
    m_lastCardPoints = m_cards[4].points();
    m_rank = TwoPair;
    return true;
  }// end if

  //check 2-1-2
  else if ( m_cards[0].points() == m_cards[1].points() &&
	    m_cards[1].points() != m_cards[2].points() &&
	    m_cards[2].points() != m_cards[3].points() &&
	    m_cards[3].points() == m_cards[4].points() ) {
    m_firstPairPoints = m_cards[0].points();
    m_secondPairPoints = m_cards[3].points();
    m_lastCardPoints = m_cards[2].points();
    m_rank = TwoPair;
    return true;
  }// end else if


  //check 1-2-2
  else if ( m_cards[0].points() != m_cards[1].points() &&
	    m_cards[1].points() == m_cards[2].points() &&
	    m_cards[2].points() != m_cards[3].points() &&
	    m_cards[3].points() == m_cards[4].points() ) {
    m_firstPairPoints = m_cards[1].points();
    m_secondPairPoints = m_cards[3].points();
    m_lastCardPoints = m_cards[0].points();
    m_rank = TwoPair;
    return true;
  }// end else if

  return false;  
}// end isTwoPair



/******************************************************************
 *                                                                *
 * Name:          isThreeOfAKind()                                *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - FIVE is a valid integer greater than 0        *
 *                                                                *
 * PostCondition: - returns true if the hand contains a three of  *
 *                  a kind                                        *
 *                - m_tripletPoints is populated with the         *
 *                  point value of the three of a kind            *
 *                - m_rank is populated as ThreeOfAKind           *
 *                                                                *
 *****************************************************************/
bool PokerHand::isThreeOfAKind() {
  //check 3-1-1
  if ( m_cards[0].points() == m_cards[1].points() &&
       m_cards[1].points() == m_cards[2].points() &&
       m_cards[2].points() != m_cards[3].points() &&
       m_cards[3].points() != m_cards[4].points() ) {
    m_tripletPoints = m_cards[0].points();
    m_rank = ThreeOfAKind;
    return true;
  }// end if

  //check 1-3-1
  else if ( m_cards[0].points() != m_cards[1].points() &&
	    m_cards[1].points() == m_cards[2].points() &&
	    m_cards[2].points() == m_cards[3].points() &&
	    m_cards[3].points() != m_cards[4].points() ) {
    m_tripletPoints = m_cards[1].points();
    m_rank = ThreeOfAKind;
    return true;
  }// end else if


  //check 1-1-3
  else if ( m_cards[0].points() != m_cards[1].points() &&
	    m_cards[1].points() != m_cards[2].points() &&
	    m_cards[2].points() == m_cards[3].points() &&
	    m_cards[3].points() == m_cards[4].points() ) {
    m_tripletPoints = m_cards[2].points();
    m_rank = ThreeOfAKind;
    return true;
  }// end else if

return false;
}//end isThreeOfAkind



/******************************************************************
 *                                                                *
 * Name:          isStraight()                                    *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - isSequence() returns a true or false          *
 *                                                                *
 * PostCondition: - returns true if the hand is a straight        *
 *                - m_lastCardPoints is populated with the        *
 *                  point value of the high card in the straight  *
 *                - m_rank is populated as Straight               *
 *                                                                *
 *****************************************************************/
bool PokerHand::isStraight() {
  if ( isSequence() &&
       m_cards[0].points() != 10 ) {
    m_lastCardPoints = m_cards[4].points();
    m_rank = Straight;
    return true;
  }// end if
  return false;
}// end isStraight



/******************************************************************
 *                                                                *
 * Name:          isFlush()                                       *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - isAllOneSuit() returns a true or false        *
 *                                                                *
 * PostCondition: - returns true if the hand is a all same suit   *
 *                - m_lastCardPoints is populated with the        *
 *                  point value of the high card in the flush     *
 *                - m_rank is populated as Flush                  *
 *                                                                *
 *****************************************************************/
bool PokerHand::isFlush() {
  if (isAllOneSuit() &&
      isSequence() == false ) {
    m_lastCardPoints = m_cards[4].points();
    m_rank = Flush;
    return true;
  }// end if
  return false;
}// end isFlush



/******************************************************************
 *                                                                *
 * Name:          isFullHouse()                                   *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - isOnePair() returns a true or false           *
 *                - isThreeOfAKind() returns a true or false      *
 *                                                                *
 * PostCondition: - returns true if the hand has a pair and trips *
 *                - m_rank is populated as ThreeOfAKind           *
 *                                                                *
 *****************************************************************/
bool PokerHand::isFullHouse() {
  //check 3-2
  if ( m_cards[0].points() == m_cards[1].points() &&
       m_cards[1].points() == m_cards[2].points() &&
       m_cards[2].points() != m_cards[3].points() &&
       m_cards[3].points() == m_cards[4].points() ) {
    m_tripletPoints = m_cards[0].points();
    m_firstPairPoints = m_cards[3].points();
    m_rank = FullHouse;
    return true;
  }// end if

  //check 2-3
  else if ( m_cards[0].points() == m_cards[1].points() &&
	    m_cards[1].points() != m_cards[2].points() &&
	    m_cards[2].points() == m_cards[3].points() &&
	    m_cards[3].points() == m_cards[4].points() ) {
    m_tripletPoints = m_cards[2].points();
    m_firstPairPoints = m_cards[0].points();
    m_rank = FullHouse;
    return true;
  }// end else if  

  return false;
}// end isFullHouse



/******************************************************************
 *                                                                *
 * Name:          isFourOfAKind()                                 *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                                                                *
 * PostCondition: - returns true if the hand has four of a kind   *
 *                - m_rank is populated as FourOfAKind            *
 *                - m_quadrupletPoints is populated with the      *
 *                  points value of the set of four of a kind     *
 *                - m_lastCardPoints is set as the value of the   *
 *                  last card                                     *
 *                                                                *
 *****************************************************************/
bool PokerHand::isFourOfAKind() {
  if ( m_cards[0].points() == m_cards[1].points() &&
       m_cards[1].points() == m_cards[2].points() &&
       m_cards[2].points() == m_cards[3].points() &&
       m_cards[3].points() != m_cards[4].points() ) {
    m_quadrupletPoints = m_cards[0].points();
    m_lastCardPoints = m_cards[4].points();
    m_rank = FourOfAKind;
    return true;
  }//end if
  else if ( m_cards[0].points() != m_cards[1].points() &&
	    m_cards[1].points() == m_cards[2].points() &&
	    m_cards[2].points() == m_cards[3].points() &&
	    m_cards[3].points() == m_cards[4].points() ) {
    m_quadrupletPoints = m_cards[1].points();
    m_lastCardPoints = m_cards[0].points();
    m_rank = FourOfAKind;
    return true;
  }// end else if
  return false;
}//end isTFourOfAKind



/******************************************************************
 *                                                                *
 * Name:          isStraightFlush()                               *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - isStraight() and isFlush() both return either *
 *                  true or false values                          *
 *                                                                *
 * PostCondition: - returns true if the hand is in sequence and   *
 *                  all the same suit                             *
 *                - m_rank is populated as StraightFlush          *
 *                - m_lastCardPoints is set as the value of the   *
 *                  last card, which is the high card             *
 *                                                                *
 *****************************************************************/
bool PokerHand::isStraightFlush() {
  if ( isSequence() && 
       isAllOneSuit() &&
       m_cards[0].points() != 10 ) {
    m_lastCardPoints = m_cards[4].points();
    m_rank = StraightFlush;
    return true;
  }// end if
  return false;
}// end isStraightFlush



/******************************************************************
 *                                                                *
 * Name:          isRoyalFlush()                                  *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - isSequence() and isAllOneSuit() both return   *
 *                  true or false values                          *
 *                                                                *
 * PostCondition: - returns true if the hand is in sequence and   *
 *                  all the same suit and the highcard is an ace  *
 *                - m_rank is populated as RoyalFlush             *
 *                                                                *
 *****************************************************************/
bool PokerHand::isRoyalFlush() {
  if ( isSequence() && 
       isAllOneSuit() && 
       m_cards[0].points() == 10 ) {
    m_rank = RoyalFlush;
    return true;
  }// end if
  return false;
}//end isRoyalFlush


/******************************************************************
 *                                                                *
 * Name:          getRank()                                       *
 *                                                                *
 * PreCondition:  - m_rank is populated                           *
 *                                                                *
 * PostCondition: - m_rank is returned                            *
 *                                                                *
 *****************************************************************/
PokerHand::pRank PokerHand::getRank() {
  return m_rank;
}//end getRank


/******************************************************************
 *                                                                *
 * Name:          cmp()                                           *
 *                                                                *
 * PreCondition:  - getRank returns a valid rank                  *
 *                - both pokerhands are populated with valid      *
 *                  card objects                                  *
 *                - m_quadrupletPoints, m_lastCardPoints,         *
 *                  m_tripletPoints, m_firstPairPoints are all    *
 *                  populated with valid integers                 *
 *                                                                *
 * PostCondition: - returns a negative number if the host hand is *
 *                  inferior to the compared hand                 *
 *                - returns a positive number if the host hand is *
 *                  superior to the compared hand                 *
 *                - returns a 0 if the two hands are tie          *
 *                                                                *
 *****************************************************************/
int PokerHand::cmp(PokerHand &otherHand) {
  if (( getRank() -  otherHand.getRank()) == 0) {
    switch (getRank()) {
    case StraightFlush:
      return m_lastCardPoints - otherHand.m_lastCardPoints;
      break;

    case FourOfAKind:
      if ( m_quadrupletPoints - otherHand.m_quadrupletPoints == 0)
	return m_lastCardPoints - otherHand.m_lastCardPoints;
      return m_quadrupletPoints - otherHand.m_quadrupletPoints;
      break;

    case FullHouse:
      if ( m_tripletPoints - otherHand.m_tripletPoints == 0 )
	return  m_firstPairPoints - otherHand.m_firstPairPoints;
      return m_tripletPoints - otherHand.m_tripletPoints;
      break;

    case Flush:
      return m_lastCardPoints - otherHand.m_lastCardPoints;
      break;

    case Straight:
      return m_lastCardPoints - otherHand.m_lastCardPoints;
      break;

    case ThreeOfAKind:
      if ( m_tripletPoints - otherHand.m_tripletPoints == 0 )
	return m_lastCardPoints - otherHand.m_lastCardPoints;
      return m_tripletPoints - otherHand.m_tripletPoints;
      break; 

    case TwoPair:
      if ( m_secondPairPoints - otherHand.m_secondPairPoints == 0 ) {
	if ( m_firstPairPoints - otherHand.m_firstPairPoints == 0 )
	  return m_lastCardPoints - otherHand.m_lastCardPoints;
	return  m_firstPairPoints - otherHand.m_firstPairPoints;
      }// end if
      return  m_secondPairPoints - otherHand.m_secondPairPoints;
      break;
      
    case OnePair:
      if ( m_firstPairPoints - otherHand.m_firstPairPoints == 0 )
	return m_lastCardPoints - otherHand.m_lastCardPoints;
      return m_firstPairPoints - otherHand.m_firstPairPoints;
      break;

    case HighCard:
      return m_lastCardPoints - otherHand.m_lastCardPoints;
      break;

    default:
      return 0;
    }// end switch
  }// end if

  return (getRank() - otherHand.getRank());
}// end cmp




/******************************************************************
 *                                                                *
 * Name:          isSequence()                                    *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                - pokerhand is sorted in ascending order        *
 *                                                                *
 * PostCondition: - returns true if the cards are in sequence in  *
 *                  ascending order, otherwise false              *
 *                                                                *
 *****************************************************************/
bool PokerHand::isSequence() {
  int i = 1;
  while(i < 4) {
    if (((m_cards[i].points() + 1) != (m_cards[i + 1].points())))
      return false;
    i++;
  }// end while
  return true;
}//end isSequence


/******************************************************************
 *                                                                *
 * Name:          isAllOneSuit()                                  *
 *                                                                *
 * PreCondition:  - m_cards is populated with valid card objects  *
 *                                                                *
 * PostCondition: - returns true if the cards are in sequence in  *
 *                  ascending order, otherwise false              *
 *                                                                *
 *****************************************************************/
bool PokerHand::isAllOneSuit() {
  int i = 0;
  while(i < 4) {
    if (m_cards[i].suit() != m_cards[i + 1].suit())
      return false;
    i++;
  }// end while
  return true;
}// end isAllOneSuit


/******************************************************************
 *                                                                *
 * Name:          setRank()                                       *
 *                                                                *
 * PreCondition:  - all function calls return true or false values*
 *                                                                *
 * PostCondition: - m_rank is set to the appropriate rank         *
 *                                                                *
 *****************************************************************/
void PokerHand::setRank() {
  if (isRoyalFlush())
    m_rank = RoyalFlush;
  else if (isStraightFlush())
    m_rank = StraightFlush;
  else if (isFourOfAKind())
    m_rank = FourOfAKind;
  else if (isFlush())
    m_rank = Flush;
  else if (isStraight())
    m_rank = Straight;
  else if (isThreeOfAKind())
    m_rank = ThreeOfAKind;
  else if (isTwoPair())
    m_rank = TwoPair;
  else if (isFullHouse())
    m_rank = FullHouse;
  else if (isOnePair())
    m_rank = OnePair;
  else if (isHighCard())
    m_rank = HighCard;
  else 
    m_rank = NoRank;
}// end setRank
