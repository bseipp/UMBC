#include <iostream>

using namespace std;
#include "Time.h"
#include "Train.h"
#include "TrainStation.h"

int main() {

  Train* ner111 = new Train( 111, Time(13, 25), "Boston" );
  
  ner111->addCar( TrainCar::Locomotive );
  ner111->addCar( TrainCar::CoachClass );
  ner111->addCar( TrainCar::CoachClass );
  ner111->addCar( TrainCar::CoachClass );
  ner111->addCar( TrainCar::BusinessClass );
  ner111->addCar( TrainCar::SnackCar );

  Train *ner531 = new Train( 531, Time(13, 30), "Montreal" );
  
  ner531->addCar( TrainCar::Locomotive );
  ner531->addCar( TrainCar::CoachClass );
  ner531->addCar( TrainCar::CoachClass );
  ner531->addCar( TrainCar::CoachClass );
  ner531->addCar( TrainCar::CoachClass );
  ner531->addCar( TrainCar::SnackCar );
  ner531->addCar( TrainCar::SleepingCar );
  ner531->addCar( TrainCar::SleepingCar );

  Train *ner227 = new Train( 227, Time(13, 40), "Lynchburg");
  
  ner227->addCar( TrainCar::Locomotive );
  ner227->addCar( TrainCar::CoachClass );
  ner227->addCar( TrainCar::CoachClass );
  ner227->addCar( TrainCar::CoachClass );
  ner227->addCar( TrainCar::SnackCar );

  Train *invalid = new Train( 0, Time(13, 50), "Nowhere" );

  invalid->addCar( TrainCar::Locomotive );

  Train *ner032 = new Train( 32, Time(13, 55), "New York" );
  
  ner032->addCar( TrainCar::Locomotive );
  ner032->addCar( TrainCar::CoachClass );
  ner032->addCar( TrainCar::CoachClass );
  ner032->addCar( TrainCar::CoachClass );
  ner032->addCar( TrainCar::SnackCar );

 
  TrainStation unionStation(4);

  unionStation.addTrain( ner111 );
  
  unionStation.addTrain( ner531 );
  unionStation.addTrain( ner227 );
  unionStation.addTrain( invalid );
  unionStation.addTrain( ner032);
  
  unionStation.departureBoard( Time(13, 00), 60 );

  unionStation.departure( ner111 );
  
  unionStation.addTrain( ner032 );
  
  unionStation.departureBoard( Time(13, 00), 60 );

  unionStation.departure( ner531 );

  unionStation.departureBoard( Time(13, 30), 60 );

  unionStation.departure( invalid );

  unionStation.removeTrain( invalid );

  unionStation.departureBoard( Time(13, 30), 60 );
  
  return 0;
}
