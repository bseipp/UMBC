#ifndef TRAINSTATION_H
#define TRAINSTATION_H

class TrainStation {
 public:

  // Create a station with NTRACKS tracks
  // Create m_tracks array and initialize track pointers to NULL
  TrainStation();

  // Create a station with numTracks tracks
  // Create m_tracks array and initialize track pointers to NULL
  TrainStation( int numTracks );

  // Destructor deletes the dynamically allocated array m_tracks
  ~TrainStation();
  
  // Assign train pointed to by tPtr to a track
  // Return true if successful; false if no track available
  bool addTrain( Train* tPtr );

  // Set the track pointer for the specified train to NULL
  // Return true if successful; false if the train is not
  // on one of the tracks
  bool removeTrain( Train* tPtr);

  // Return a pointer to the train on track trackNum
  Train* getTrainOnTrack( int trackNum ) const;

  // Check if tPtr points to a valid train and is on a track; 
  // if so, print a departure message, remove the train from 
  // the track (set the track's poiner to NULL), and return 
  // true; otherwise, return false.
  bool departure( Train* tPtr );

  // Print the departure board for all trains departing between
  // time and time+min
  void departureBoard( const Time& time, int min );

  // Default number of tracks in a station
  static const int NTRACKS = 5;

 private:
  int m_numTracks;     // number of tracks
  Train** m_tracks;    // array of train pointers
};


#endif
