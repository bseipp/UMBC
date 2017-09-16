/********************************************************************
 * File:    sched.cpp                                               *
 * Project: CMSC 202 Project 1, Spring 2016                         *
 * Author:  Brian Seipp                                             *
 * Date:    02/22/2016                                              *
 * Section: 19                                                      *
 * E-mail:  seipp1@umbc.edu                                         *
 ********************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include "sched.h"

using namespace std;

// FUNCTION PROTOTYPES -- DO NOT CHANGE!

// sort() - sorts an array of floats returning sorted indices
// On return, indx[] is an array of indices such that data[indx[0]], 
// data[indx[1]], ..., data[indx[len-1]] is data[] in ascending order.
//
// Parameters
//    data[] - float array of data to be ordered
//    indx[] - int array, same length as data[], to hold indices
//    len - int specifying the length of data[] and indx[]

void sort(float data[], int indx[], int len);

// sched() - schedules events given start and end times, and indx[] from sort
// Returns number of events scheduled; on return, scheduled[] contains 
// indices of scheduled events (e.g. startTime[scheduled[0]] is the start
// time of the first schedled event).
//
// Parameters
//    startTime[] - float array of event start times
//    endTime[] - float array of event end times
//    indx[] - array of indices that orders the end times
//    scheduled[] - int array to hold indices of scheduled events
//    len - int specifying the length of the arrays
// Returns
//    int value specifying number of events scheduled

int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len);

// printEvent() - prints an event to the console
// Converts float start and end times to hh:mm format and prints times
// along with description.  E.g. Study Session from 12.5 to 13.25 should
// print as "12:30 - 13:15 Study Session"
//
// Parameters
//    startTime - float event start time
//    endTime - float event end time
//    description - string event description

void printEvent(float startTime, float endTime, string description);

// MAIN PROGRAM - DO NOT CHANGE!

int main() {

  int indx[NUM_EVENTS];
  int scheduledEvents[NUM_EVENTS];
  int numSched;

  // Sort by event ending times
  sort(endTime, indx, NUM_EVENTS);

  // Call greedy scheduling algorithm
  numSched = sched(startTime, endTime, indx, scheduledEvents, NUM_EVENTS);
  
  // Display scheduled events
  for (int i = 0; i < numSched; i++)
    printEvent(startTime[scheduledEvents[i]], endTime[scheduledEvents[i]],
	       description[scheduledEvents[i]]);

  return 0;
}

/******************************************************************
 *                                                                *
 * Name:          sort()                                          *
 *                                                                *
 * PreCondition:  len is positive, values in data are positive    *
 *                                                                *
 * PostCondition: indx array is populated with the sorted indexes *
 *                corresponding to the data[] array               *
 *                                                                *
 *****************************************************************/

void sort(float data[], int indx[], int len) {

  int temp = 0; // temp variable holds the place of the variable being swapped

  // indx array is initialized from 0 to len-1 with values 0, 1, 2, 3, 4, ... , len-1.
  for (int indexCount = 0; indexCount < len; indexCount++)
    indx[indexCount] = indexCount;

  // These loops will check each element of the data array, put the smallest 
  //in the first position of the indx[] array. Then the loop will move to 
  //the second position on indx, and repeat the process until the array indx 
  //is a sorted version of the the data indx[]
  for (int nextSmallest = 0; nextSmallest < len; nextSmallest++){

    for (int comparedAgainst = nextSmallest + 1; comparedAgainst < len; comparedAgainst++){

      // if the value at indx[nextSmallest] is larger than that at indx[comparedAgainst], 
      //the two indexes are swapped
      if (data[indx[comparedAgainst]] < data[indx[nextSmallest]]) {
	temp = indx[nextSmallest]; 
	indx[nextSmallest] = indx[comparedAgainst];
	indx[comparedAgainst] = temp;

      }// end if
    }// end for comparedAgainst
  }// end for nextSmallest
}// end sort()

/******************************************************************
 *                                                                *
 * Name:          sched()                                         *
 *                                                                *
 * PreCondition:  startTime, endTime, and len are positive        *
 *                indx contained sorted indices from 0 to len     *
 *                                                                *
 * PostCondition: scheduled[] is populated with the optimal       *
 *                schedule based on the algorithm:                *
 *                                                                *
 *                1. Sort events in ascending order               *
 *                2. Schedule first event on sorted list; remove  *
 *                   the event schedule and all events that start *
 *                   before the scheduled event ends.             *
 *                3. Repeat step 2 until there are no more events *
 *                                                                *
 *****************************************************************/

int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len) {

  int classCount = 0;

  // First class is scheduled in the scheduled[] array
  scheduled[classCount] = indx[0];

  int lastScheduled = 0; // The most recently scheduled class marked 

  int numberScheduled = 1; // Counter for number of scheduled events

  // This loop will cycle through all classes, if the class has a start time after 
  //the most recently scheduled classes end time, it will add it to the scheduled 
  //array, then mark that class as the most recently scheduled.
  for (int unscheduledClass = 0; unscheduledClass < len; unscheduledClass++){

    if (startTime[indx[unscheduledClass]] >= endTime[indx[lastScheduled]]){
	scheduled[++classCount] = indx[unscheduledClass];
	numberScheduled++;
	lastScheduled = unscheduledClass;
	
    }// end if 
  }// end for unscheduledClass
  return numberScheduled;
}// end sched()

/******************************************************************
 *                                                                *
 * Name:          printEvent()                                    *
 *                                                                *
 * PreCondition:  startTime and endTime are positive              *
 *                                                                *
 * PostCondition: pretty prints an event to the console. Times    *
 *                printed in the format:                          *
 *                                                                *
 *                hh:mm - hh:mm description                       *
 *                                                                *
 *****************************************************************/

void printEvent(float startTime, float endTime, string description){

  cout.fill('0');

  int startHour = startTime; // casts start time (a float) to an integer to truncate
  // subtracts the hour portion of the start time from the start time, 
  // then multiplies the minutes by 60 to get minutes in mm form.
  int startMinute = (startTime - startHour) * 60;

  int endHour = endTime; // casts end time (a float) to an integer to truncate
  // subtracts the hour portion of the end time from the end time, 
  //then multiplies the minutes by 60 to get minutes in mm form.
  int endMinute = (endTime - endHour) * 60;

  cout << setw(2) << startHour << ":" << setw(2) << startMinute 
       << " - " << setw(2) << endHour << ":" << setw(2) << endMinute << " " << description << "\n";

}//end printEvent	     
