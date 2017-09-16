#ifndef SCHED_H
#define SCHED_H

#include <string>

using namespace std;

const int NUM_EVENTS = 10;   // number of event requests

// Event start times
float startTime[NUM_EVENTS] = 
  {7.5,  8.0,  8.0,  10.5, 11.5,  12.0, 13.0, 14.0,  16.0, 17.0};

// Event end times
float endTime[NUM_EVENTS] =
  {8.5, 10.0,  9.25, 12.5, 12.75, 12.5, 16.0, 14.75, 17.0, 18.0};

// Event descriptions
string description[NUM_EVENTS] = 
  {
    "Breakfast Club",
    "Troy and Abed in the Morning",
    "Study Group",
    "Teaching Workshop",
    "Happy Hands Club",
    "Spanish 101",
    "Treblemakers",
    "Big Cheddar Fussball Camp",
    "Delta Tau Chi",
    "Dead Poets Society"
  };

#endif
    
    
        
    
    
