#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Include student code inside a namespace

namespace P1 {
   #include "sched.cpp"
} 


// Declare function prototypes for functions student needs to implement.
// This is a re-declaration, but will catch students who change the
// function signature.

namespace P1 {
  void sort(float data[], int indx[], int len);
  int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len);
  void printEvent(float startTime, float endTime, string description);
}



int main() {

  const int n = 17 ;   // replaces NUM_EVENTS
 
  // same as before
  int indx[n];
  int scheduledEvents[n];
  int numSched;
 
  // local versions of start time, end time and descriptionn
  float startTime[n] ;
  float endTime[n] ;
  string description[n] ;
 
  startTime[ 0] = 2.3 ;   endTime[ 0] = 7.4 ;
  startTime[ 1] = 3.4 ;   endTime[ 1] = 4.7 ;
  startTime[ 2] = 5.6 ;   endTime[ 2] = 6.1 ;
  startTime[ 3] = 5.6 ;   endTime[ 3] = 5.7 ;
  startTime[ 4] = 1.4 ;   endTime[ 4] = 2.3 ;
  startTime[ 5] = 2.2 ;   endTime[ 5] = 2.5 ;
  startTime[ 6] = 3.2 ;   endTime[ 6] = 6.5 ;
  startTime[ 7] = 6.4 ;   endTime[ 7] = 6.6 ;
  startTime[ 8] = 2.4 ;   endTime[ 8] = 3.3 ;
  startTime[ 9] = 4.3 ;   endTime[ 9] = 4.8 ;
  startTime[10] = 5.6 ;   endTime[10] = 5.9 ;
  startTime[11] = 4.7 ;   endTime[11] = 6.4 ;
  startTime[12] = 1.1 ;   endTime[12] = 1.9 ;
  startTime[13] = 7.2 ;   endTime[13] = 7.7 ;
  startTime[14] = 2.2 ;   endTime[14] = 4.7 ;
  startTime[15] = 3.1 ;   endTime[15] = 3.7 ;
  startTime[16] = 4.7 ;   endTime[16] = 5.6 ;
 
  description[ 0] = "XXX  1" ;
  description[ 1] = "XXX  2" ;
  description[ 2] = "XXX  3" ;
  description[ 3] = "Event E" ;
  description[ 4] = "XXX  4" ;
  description[ 5] = "Event B" ;
  description[ 6] = "XXX  5" ;
  description[ 7] = "Event F" ;
  description[ 8] = "XXX  6" ;
  description[ 9] = "Event D" ;
  description[10] = "XXX  7" ;
  description[11] = "XXX  8" ;
  description[12] = "Event A" ;
  description[13] = "Event G" ;
  description[14] = "XXX  9" ;
  description[15] = "Event C" ;
  description[16] = "XXX 10" ;
 
 
  // Print out original data
  cout << "*** Original ***\n" ;
  for (int i=0 ; i < n ; i++) {
    P1::printEvent(startTime[i], endTime[i], description[i]) ;
  }
 
  // Sort by event ending times
  P1::sort(endTime, indx, n);

  // Check if the endTimes are actually sorted
  cout << "\n\n*** Check sort() function for correctness ***\n" ;
  bool isSorted = true ;
  for (int i=0 ; i < n-1 ; i++) {
    if (endTime[indx[i]] > endTime[indx[i+1]]) {
      isSorted = false ;
    }
  }
 
  if (isSorted) {
    cout << "The endTime array is sorted!\n" ;
  } else {
    cout << "**** BIG BUG DETECTED ****\n" ; 
    cout << "The endTime array is ***NOT*** sorted!\n" ;
  }
 
  cout << "\n\n*** Dump Events in endTime order ***\n" ;
  int j ;
  for (int i=0 ; i < n ; i++) {
    j = indx[i] ;
    cout << "indx[" << i << "] = " << j << "  " ;
    P1::printEvent(startTime[j], endTime[j], description[j]) ;
  }
   
  // Call greedy scheduling algorithm
  numSched = P1::sched(startTime, endTime, indx, scheduledEvents, n);
 
  // Display scheduled events
  cout << "\n\n***Scheduled Events***\n" ;
  for (int i = 0; i < numSched; i++)
    P1::printEvent(startTime[scheduledEvents[i]], endTime[scheduledEvents[i]],
		   description[scheduledEvents[i]]);
 
  return 0;
}
