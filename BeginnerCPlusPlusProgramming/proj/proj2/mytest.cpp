/* File: test.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 2

   The main() function in this program uses
   the Card and PokerHand classes to 
   to determine the rank of a poker hand.

*/

#include <iostream>
using namespace std ;

#include "pokerhand.h"

int main() {

  //test high card
  Card c0(Card::Spades,   14) ;
  Card c1(Card::Clubs,     4) ;
  Card c2(Card::Clubs,    12) ;
  Card c3(Card::Diamonds,  5) ;
  Card c4(Card::Hearts,   13) ;

  PokerHand Hand(c0, c1, c2, c3, c4) ;
  cout << endl;
  cout << "High Card Hand is: ";
  Hand.printCards();
  
  cout << endl << "My hand is a " ;
  Hand.printRank() ; 
  cout << endl ;

  //test One Pair
  Card d0(Card::Spades,   14) ;
  Card d1(Card::Clubs,    14) ;
  Card d2(Card::Clubs,    12) ;
  Card d3(Card::Diamonds,  5) ;
  Card d4(Card::Hearts,   13) ;

  PokerHand pairHand(d0, d1, d2, d3, d4) ;
  cout << endl;
  cout << "One Pair Hand is: ";
  pairHand.printCards();
  
  cout << endl << "My hand is a " ;
  pairHand.printRank() ; 
  cout << endl ;

  //test Two Pair
  Card e0(Card::Spades,   14) ;
  Card e1(Card::Clubs,    14) ;
  Card e2(Card::Clubs,    12) ;
  Card e3(Card::Diamonds,  5) ;
  Card e4(Card::Hearts,   12) ;

  PokerHand twoPairHand(e0, e1, e2, e3, e4) ;
  cout << endl; 
  cout << "Two Pair Hand is: ";
  twoPairHand.printCards();
  
  cout << endl << "My hand is a " ;
  twoPairHand.printRank() ; 
  cout << endl ;
  
  //test three of a kind
  Card f0(Card::Spades,   14) ;
  Card f1(Card::Clubs,    14) ;
  Card f2(Card::Clubs,    12) ;
  Card f3(Card::Diamonds,  5) ;
  Card f4(Card::Hearts,   14) ;

  PokerHand tripHand(f0, f1, f2, f3, f4) ;
  cout << endl;
  cout << "Three Of A Kind Hand is: ";
  tripHand.printCards();
  
  cout << endl << "My hand is a " ;
  tripHand.printRank() ; 
  cout << endl ;

  //test straight
  Card g0(Card::Spades,   10) ;
  Card g1(Card::Clubs,     9) ;
  Card g2(Card::Clubs,     8) ;
  Card g3(Card::Diamonds,  7) ;
  Card g4(Card::Hearts,    6) ;

  PokerHand straightHand(g0, g1, g2, g3, g4) ;
  cout << endl;
  cout << "Straight Hand is: ";
  straightHand.printCards();
  
  cout << endl << "My hand is a " ;
  straightHand.printRank() ; 
  cout << endl ;

  //test flush
  Card h0(Card::Hearts,   10) ;
  Card h1(Card::Hearts,    9) ;
  Card h2(Card::Hearts,    8) ;
  Card h3(Card::Hearts,    2) ;
  Card h4(Card::Hearts,    6) ;

  PokerHand flushHand(h0, h1, h2, h3, h4) ;
  cout << endl;
  cout << "Flush Hand is: ";
  flushHand.printCards();
  
  cout << endl << "My hand is a " ;
  flushHand.printRank() ; 
  cout << endl ;

  //test full house
  Card i0(Card::Spades,   10) ;
  Card i1(Card::Clubs,    10) ;
  Card i2(Card::Clubs,     8) ;
  Card i3(Card::Diamonds,  8) ;
  Card i4(Card::Hearts,    8) ;

  PokerHand fullHouseHand(i0, i1, i2, i3, i4) ;
  cout << endl;
  cout << "Full House Hand is: ";
  fullHouseHand.printCards();
  
  cout << endl << "My hand is a " ;
  fullHouseHand.printRank() ; 
  cout << endl ;

  //test four of a kind
  Card j0(Card::Spades,   10) ;
  Card j1(Card::Clubs,    10) ;
  Card j2(Card::Clubs,     8) ;
  Card j3(Card::Diamonds, 10) ;
  Card j4(Card::Hearts,   10) ;

  PokerHand quadsHand(j0, j1, j2, j3, j4) ;
  cout << endl;
  cout << "Four of a kind Hand is: ";
  quadsHand.printCards();
  
  cout << endl << "My hand is a " ;
  quadsHand.printRank() ; 
  cout << endl ;

  //test straight flush
  Card k0(Card::Spades,    10) ;
  Card k1(Card::Spades,     9) ;
  Card k2(Card::Spades,     8) ;
  Card k3(Card::Spades,     7) ;
  Card k4(Card::Spades,     6) ;

  PokerHand sFlushHand(k0, k1, k2, k3, k4) ;
  cout << endl;
  cout << "Straight Flush Hand is: ";
  sFlushHand.printCards();
  
  cout << endl << "My hand is a " ;
  sFlushHand.printRank() ; 
  cout << endl ;

  //test straight flush
  Card l0(Card::Spades,    10) ;
  Card l1(Card::Spades,    11) ;
  Card l2(Card::Spades,    12) ;
  Card l3(Card::Spades,    13) ;
  Card l4(Card::Spades,    14) ;

  PokerHand rFlushHand(l0, l1, l2, l3, l4) ;
  cout << endl;
  cout << "Royal Flush Hand is: ";
  rFlushHand.printCards();
  
  cout << endl << "My hand is a " ;
  rFlushHand.printRank() ; 
  cout << endl ;

  //test high card 2
  Card m0(Card::Spades,    6) ;
  Card m1(Card::Clubs,     4) ;
  Card m2(Card::Clubs,    12) ;
  Card m3(Card::Diamonds,  5) ;
  Card m4(Card::Hearts,   13) ;

  PokerHand Hand2(m0, m1, m2, m3, m4) ;
  

  //test One Pair 2
  Card n0(Card::Spades,    3) ;
  Card n1(Card::Clubs,    10) ;
  Card n2(Card::Clubs,    12) ;
  Card n3(Card::Diamonds,  5) ;
  Card n4(Card::Hearts,   10) ;

  PokerHand pairHand2(n0, n1, n2, n3, n4) ;

  //test Two Pair 2
  Card o0(Card::Spades,    5) ;
  Card o1(Card::Clubs,     5) ;
  Card o2(Card::Clubs,     2) ;
  Card o3(Card::Diamonds,  2) ;
  Card o4(Card::Hearts,   12) ;

  PokerHand twoPairHand2(o0, o1, o2, o3, o4) ;

  //test Two Pair 3
  Card z0(Card::Spades,    5) ;
  Card z1(Card::Clubs,     5) ;
  Card z2(Card::Clubs,     3) ;
  Card z3(Card::Diamonds,  3) ;
  Card z4(Card::Hearts,   12) ;

  PokerHand twoPairHand3(z0, z1, z2, z3, z4) ;

  //test Two Pair 4
  Card x0(Card::Spades,    5) ;
  Card x1(Card::Clubs,     5) ;
  Card x2(Card::Clubs,     3) ;
  Card x3(Card::Diamonds,  3) ;
  Card x4(Card::Hearts,   14) ;

  PokerHand twoPairHand4(x0, x1, x2, x3, x4) ;
  
  //test three of a kind 2
  Card p0(Card::Spades,   10) ;
  Card p1(Card::Clubs,    10) ;
  Card p2(Card::Clubs,    12) ;
  Card p3(Card::Diamonds,  5) ;
  Card p4(Card::Hearts,   10) ;

  PokerHand tripHand2(p0, p1, p2, p3, p4) ;

  //test straight 2
  Card q0(Card::Spades,   10) ;
  Card q1(Card::Clubs,     9) ;
  Card q2(Card::Clubs,     8) ;
  Card q3(Card::Diamonds,  7) ;
  Card q4(Card::Hearts,   11) ;

  PokerHand straightHand2(q0, q1, q2, q3, q4) ;

  //test flush 2
  Card r0(Card::Clubs,    2) ;
  Card r1(Card::Clubs,    9) ;
  Card r2(Card::Clubs,    8) ;
  Card r3(Card::Clubs,    2) ;
  Card r4(Card::Clubs,    6) ;

  PokerHand flushHand2(r0, r1, r2, r3, r4) ;

  //test full house 2
  Card s0(Card::Spades,   13) ;
  Card s1(Card::Clubs,    13) ;
  Card s2(Card::Clubs,     7) ;
  Card s3(Card::Diamonds,  7) ;
  Card s4(Card::Hearts,    7) ;

  PokerHand fullHouseHand2(s0, s1, s2, s3, s4) ;

  //test four of a kind 2
  Card t0(Card::Spades,    2) ;
  Card t1(Card::Clubs,    10) ;
  Card t2(Card::Clubs,     2) ;
  Card t3(Card::Diamonds,  2) ;
  Card t4(Card::Hearts,    2) ;

  PokerHand quadsHand2(t0, t1, t2, t3, t4) ;

  //test straight flush 2
  Card u0(Card::Hearts,     5) ;
  Card u1(Card::Hearts,     9) ;
  Card u2(Card::Hearts,     8) ;
  Card u3(Card::Hearts,     7) ;
  Card u4(Card::Hearts,     6) ;

  PokerHand sFlushHand2(u0, u1, u2, u3, u4) ;

  PokerHand testHands[] = { Hand, Hand2, 
			    pairHand, pairHand2, 
			    twoPairHand, twoPairHand2,
			    tripHand, tripHand2,
			    straightHand, straightHand2,
			    flushHand, flushHand2,
			    fullHouseHand, fullHouseHand2,
			    quadsHand, quadsHand2,
			    sFlushHand, sFlushHand2,
			    twoPairHand2, twoPairHand3,
			    twoPairHand3, twoPairHand4 };

  for (int i = 0; i < 22; i += 2) {
    cout << endl << "*************************" << endl;

    cout << "These hands are : ";
    testHands[i].printRank();

    cout << endl;
    if (testHands[i].cmp(testHands[i + 1]) > 0) {
      cout << "My hand beats yours.\n" ;
    } else if (testHands[i].cmp(testHands[i + 1]) < 0) {
      cout << "Your hand beats mine.\n" ;
    } else {
      cout << "Our hands are tied.\n" ;
    }

    cout << "\nMy hand is:\n" ;
    testHands[i].printCards() ;
    cout << "\nYour hand is:\n" ;
    testHands[i + 1].printCards() ;
  }//end for
}
