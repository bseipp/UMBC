#include <iostream>

using namespace std;
#include "TrainCar.h"
#include "Train.h"

int main() {
  
  Train* newTrain = new Train( 111, Time(13, 25), "Boston" ) ;

  newTrain -> addCar ( TrainCar::Locomotive ) ;
  cout << "First train, only Locomotive: " << endl << *newTrain << endl << endl ;
  
  newTrain -> addCar ( TrainCar::Locomotive ) ;
  cout << "Second train, second Locomotive: " << endl << *newTrain << endl << endl ;

  newTrain -> addCar ( TrainCar::BusinessClass ) ;
  cout << "Third train, 2 Loco, 1 BC: " << endl << *newTrain << endl << endl ;

  newTrain -> addCar ( TrainCar::Locomotive ) ;
  cout << "Fourth train, 3 Loco, 1 BC: " << endl << *newTrain << endl << endl ;

  newTrain -> addCar ( TrainCar::BusinessClass ) ;
  cout << "Fifth train, 3 Loco, 2 BC: " << endl << *newTrain << endl << endl ;

  Train* newTrain2 = new Train ( 111, Time(13, 25), "New York" ) ;
  newTrain2 -> addCar ( TrainCar::BusinessClass ) ;
  cout << "New Train, only BC: " << endl << *newTrain2 << endl << endl;

  newTrain -> addCar ( TrainCar::CoachClass ) ;
  cout << "6th Train, 3 loco, 2 bc, 1 cc: " << endl << *newTrain << endl << endl ;

  newTrain -> addCar ( TrainCar::CoachClass ) ;
  cout << "7th Train, 3 loco, 2 bc, 2 cc: " << endl << *newTrain << endl << endl ;

  newTrain2 -> addCar ( TrainCar::CoachClass ) ;
  cout << "New Train, 1 BC, 1 CC: " << endl << *newTrain2 << endl << endl;
  
  Train* newTrain3 = new Train ( 111, Time(13, 25), "New York" ) ;
  newTrain3 -> addCar ( TrainCar::CoachClass ) ;
  cout << "New Train 2, only CC: " << endl << *newTrain3 << endl << endl;

  newTrain -> addCar ( TrainCar::SleepingCar ) ;
  cout << "8th Train, 3 loco, 2bc, 2cc, 1sc: " << endl << *newTrain << endl << endl ;

  newTrain -> addCar ( TrainCar::SleepingCar ) ;
  cout << "8th Train, 3 loco, 2bc, 2cc, 2sc: " << endl << *newTrain << endl << endl ;
   
  Train* newTrain4 = new Train ( 111, Time(13, 25), "Baltimore" ) ;
  newTrain4 -> addCar ( TrainCar::SleepingCar ) ;
  cout << "New Train 3, 1sc" << endl << *newTrain4 << endl << endl ;
  
  newTrain -> addCar ( TrainCar::DiningCar ) ;
  cout << "9th Train, 3 loco, 2bc, 2cc, 1dc, 2sc: " << endl << *newTrain << endl << endl ;

  newTrain4 -> addCar ( TrainCar::DiningCar ) ;
  cout << "Train 3, 1dc, 1sc: " << endl << *newTrain4 << endl << endl;

  newTrain3 -> addCar ( TrainCar::DiningCar ) ;
  cout << "New Train 2, only CC, no DC present: " << endl << *newTrain3 << endl << endl;

  newTrain -> addCar ( TrainCar::SnackCar ) ;
  cout << "10th Train, 3 loco, 2bc, 1snackc, 2cc, 1dc, 2sc: " << endl << *newTrain << endl << endl ;
  
  Train* newTrain5 = new Train ( 111, Time(13, 25), "Baltimore" ) ;

  newTrain5 -> addCar ( TrainCar::SleepingCar ) ;
  newTrain5 -> addCar ( TrainCar::SleepingCar ) ;
  newTrain5 -> addCar ( TrainCar::SleepingCar ) ;
  newTrain5 -> addCar ( TrainCar::SleepingCar ) ;
  newTrain5 -> addCar ( TrainCar::SnackCar ) ;

  cout << "New Train 4, 2 loco, 2 cc, 1 snack, 3 cc, 1dc, 4sc: " << endl << *newTrain5 << endl << endl;

  newTrain5 -> removeCar ( TrainCar::SleepingCar ) ;
  cout << "New Train 4, 2 loco, 2 cc, 1 snack, 3 cc, 1dc, 3sc: " << endl << *newTrain5 << endl << endl;

  newTrain5 -> removeCar ( TrainCar::DiningCar ) ;
  cout << "New Train 4, 2 loco, 2 cc, 1 snack, 3 cc: " << endl << *newTrain5 << endl << endl;

  return 0;

}// end main
