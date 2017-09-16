#include <iostream>
using namespace std;

#include "Train.h"
#include "TrainStation.h"

TrainStation::TrainStation() : m_numTracks(TrainStation::NTRACKS) {
  m_tracks = new Train*[m_numTracks];
  for ( int i = 0; i < m_numTracks; i++ )
    m_tracks[i] = NULL;
}

TrainStation::TrainStation( int numTracks) : m_numTracks(numTracks) {
  m_tracks = new Train*[m_numTracks];
  for ( int i = 0; i < m_numTracks; i++ )
    m_tracks[i] = NULL;
}

TrainStation::~TrainStation() {
  if ( m_tracks != NULL ) {
    for ( int i = 0; i < m_numTracks; i++ ) 
      if ( m_tracks[i] != NULL ) {
	delete m_tracks[i];
	m_tracks[i] = NULL;
      }
    delete [] m_tracks;
    m_tracks = NULL;
  }
}
 
bool TrainStation::addTrain( Train* tPtr ) {
  // Check for an empty track; if found, set track's pointer to tPtr
  for ( int i = 0; i < m_numTracks; i++ ) 
    if ( m_tracks[i] == NULL ) {
      m_tracks[i] = tPtr;
      return true;
    }
  // If no empty track, print message and return false
  cerr << "Error in TrainStation::addTrain() : there are no tracks available." << endl;
  return false;
}

bool TrainStation::removeTrain( Train* tPtr ) {
  // Look for tPtr on a track; if found, set track's pointer to NULL
  for ( int i = 0; i < m_numTracks; i++ ) {
    if ( m_tracks[i] == tPtr ) {
      delete m_tracks[i];             
      m_tracks[i] = NULL;
      return true;
    }
  }
  // If train not found on a track, return false
  return false;
}

Train* TrainStation::getTrainOnTrack( int trackNum ) const {
  
  // Check trackNum is valid
  if ( trackNum < 0 || trackNum >= m_numTracks ) {
    cerr << "Error in TrainStation::getTrainOnTrack() : invalid track number."
	 << endl;
    return NULL;
  }

  // Check trackNum is a non-empty track
  if ( m_tracks[trackNum] == NULL ) {
    cerr << "Error in TrainStation::getTrainOnTrack() : track is empty."
	 << endl;
    return NULL;
  }

  // Return pointer to train on track trackNum
  return m_tracks[trackNum];
}

bool TrainStation::departure( Train* tPtr ) {
  // Find train tPtr on a track; if found, print departure message,
  // remove train from track, adn return true
  for ( int i = 0; i < m_numTracks; i++ )
    if ( m_tracks[i] == tPtr && tPtr->isValid() ) {
      cout << "Train #" << tPtr->getNumber() << " is departing." << endl;
      removeTrain( tPtr );
      return true;
    }
  // If train tPtr not on a track, return false
  return false;
}

 
void TrainStation::departureBoard( const Time& time, int min ) {

  // Print heading and starting time
  cout << endl << "DEPARTURES [" << time << "]" << endl << endl;

  // Loop over tracks; if track is not empty, and departure time
  // is between time and time+min, print train information
  for ( int i = 0; i < m_numTracks; i++ ) {
    if ( m_tracks[i] != NULL ) {
      Time depTime = m_tracks[i]->getDepartureTime();
      if ( time < depTime && depTime < time + min ) {
	cout << "Track " << i << ": Train #"  
	     << m_tracks[i]->getNumber() << " to "
	     << m_tracks[i]->getDestination() << " departs at "
	     << m_tracks[i]->getDepartureTime() << endl << endl;
	cout << "     " << *(m_tracks[i]) << endl << endl;
      }
    }
  }
}
