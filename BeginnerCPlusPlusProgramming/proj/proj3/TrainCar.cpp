//
// TrainCar.cpp
// 
// CMSC 202 Project file
//
// COMPLETE THE IMPLEMENTATION AS INSTRUCTED
//

#include <iostream>
using namespace std;

#include "TrainCar.h"

TrainCar::TrainCar() : m_next( NULL ), m_type( NoType )
{ /* empty constructor body */ }

TrainCar::TrainCar( TrainCar::cType car ) : m_next( NULL ), m_type( car )
{ /* empty constructor body */ }

void TrainCar::setType( TrainCar::cType car ) {
  m_type = car;
}

TrainCar::cType TrainCar::getType() const {
  return m_type;
}

ostream& operator<<(ostream &outStream, const TrainCar& car)
{
  switch (car.getType()) {
  case TrainCar::Locomotive :
    return outStream << "// Locomotive ]]";


  case TrainCar::CoachClass :
    return outStream << "[ oo Coach oo ]";

  case TrainCar::BusinessClass :
    return outStream << "[ Business ]";

  case TrainCar::DiningCar :
    return outStream << "[ - Dining - ]";

  case TrainCar::SnackCar :
    return outStream << "[ -- Snack -- ]";

  case TrainCar::SleepingCar :
    return outStream << "[ o Sleeper o ]";

  default:
    return outStream << "[[[Invalid Car]]]";
  }// end switch
}// end overloaded << operator function

