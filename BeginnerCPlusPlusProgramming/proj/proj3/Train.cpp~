//
// Train.cpp
// 
// CMSC 202 Project File
//
// TWO CONSTRUCTORS ARE GIVEN.  IMPLEMENT THE REMAINDER OF
// THE CLASS AND THE OVERLOADED INSERTION OPERATOR
//


#include <iostream>
using namespace std;

#include "Train.h"
#include "TrainCar.h"

/******************************************************************
 *                                                                *
 * Name:          Train (Default Constructor)                     *
 *                                                                *
 * PreCondition:  None                                            *
 *                                                                *
 * PostCondition: - creates a default Train object that           *
 *                  initializes variables and creates a dummy     *
 *                  node to start the trains linked list.         *
 *                                                                *
 *****************************************************************/

Train::Train() : m_number(0), m_departs( Time() ), m_destination ( "" ),
		 m_hasSnackCar(false), m_numCoachClass(0), 
		 m_numBusinessClass(0), m_numSleepingCar(0) {
  m_head = new TrainCar(); // dummy node
}

/******************************************************************
 *                                                                *
 * Name:          Train (Non-Default Constructor)                 *
 *                                                                *
 * PreCondition:  None                                            *
 *                                                                *
 * PostCondition: - creates a default Train object that           *
 *                  initializes variables and creates a dummy     *
 *                  node to start the trains linked list.         *
 *                                                                *
 *****************************************************************/

Train::Train( int num, Time dep, string dest) 
  : m_number(num), m_departs(dep), m_destination(dest),
    m_hasSnackCar(false), m_numCoachClass(0), 
    m_numBusinessClass(0), m_numSleepingCar(0) {
  m_head = new TrainCar(); // dummy node
}


/******************************************************************
 *                                                                *
 * Name:          ~Train (Destructor)                             *
 *                                                                *
 * PreCondition:  Train object created                            *
 *                                                                *
 * PostCondition: - cycles through Train list, deletes each car   *
 *                                                                *
 *****************************************************************/

Train::~Train()
{
  TrainCar *travPtr = m_head ;
  TrainCar *tempPtr = NULL ;

  while ( ( travPtr != NULL ) )
    {
      tempPtr = travPtr -> m_next;
      delete travPtr ;
      travPtr = tempPtr ;
    }// end while
}// end destructor for train





/******************************************************************
 *                                                                *
 * Name:          addCar                                          *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - checks type of traincar, calls the insert     *
 *                  function for that type of train car.          *
 *                                                                *
 *****************************************************************/

void Train::addCar( TrainCar::cType car ) 
{
  if ( car == TrainCar::Locomotive )
    {
      insertLocomotive();
    }
  else if ( car == TrainCar::BusinessClass )
    {
      insertBusinessClass();
    }
  else if ( car == TrainCar::CoachClass )
    {
      insertCoachClass();
    }
  else if ( car == TrainCar::SleepingCar )
    {
      insertSleepingCar();
    }
  else if ( car == TrainCar::DiningCar )
    {
    }
  else if ( car == TrainCar::SnackCar )
    {
      insertSnackCar();
    }

}//end addCar





/******************************************************************
 *                                                                *
 * Name:          operator<< (trains)                             *
 *                                                                *
 * PreCondition:  train exists                                    *
 *                                                                *
 * PostCondition: Cycles through train and calls operator<< for   *
 *                each traincar                                   *
 *****************************************************************/

ostream& operator<<(ostream &outStream, const Train& t) 
{

  TrainCar *travPtr = t.m_head -> m_next ;
  while ( travPtr != NULL )
    { 
      outStream << *travPtr ;
      travPtr = travPtr -> m_next ;
    }//end while
  return outStream ;
}//end operator << overload





/******************************************************************
 *                                                                *
 * Name:          insertLocomotive                                *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - adds a locomotive to the front of the train   *
 *                                                                *
 *****************************************************************/

void Train::insertLocomotive() 
{
  TrainCar *newCar = new TrainCar( TrainCar::Locomotive );
 
  if (m_head -> m_next == NULL) {
    m_head -> m_next = newCar ;
  }// end if 
  else {
    newCar -> m_next = m_head -> m_next ;
    m_head -> m_next = newCar ;
  }//end else
}//end inserLocomotive





/******************************************************************
 *                                                                *
 * Name:          insertBusinessClass                             *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - adds a business class to the train after the  *
 *                  last locomotive                               *
 *                                                                *
 *****************************************************************/

void Train::insertBusinessClass()
{
  TrainCar *travPtr = m_head ;
  TrainCar *newCar = new TrainCar( TrainCar::BusinessClass ) ;

  if (m_head -> m_next == NULL) 
    {
      m_head -> m_next = newCar ;
    }// end if for no train
  else
    {
      //find the last locomotive in the list
      while ( ( travPtr -> m_next != NULL ) &&
	      ( travPtr -> m_next -> getType() == TrainCar::Locomotive ) )
	{
	  travPtr = travPtr -> m_next;
	}// end while
      
      // insert new train car
      newCar -> m_next = travPtr -> m_next ;
      travPtr -> m_next = newCar ;
    }// end else

  if ( hasCar ( TrainCar::SnackCar ) )
    {
      removeCar( TrainCar::SnackCar );
      addCar( TrainCar::SnackCar );
    }//end moving snack car

}//end insert business class





/******************************************************************
 *                                                                *
 * Name:          insertCoachClass                                *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - goes to the last locomotive, if there are no  *
 *                  business class cars, add a coach car there    *
 *                - if there is a business car, go to the end of  *
 *                  business cars, then add a coach car           *
 *                - if there is a snack car present, the snack    *
 *                  car is removed, and a snack car is added back *
 *                                                                *
 *****************************************************************/

void Train::insertCoachClass()
{
  TrainCar *travPtr = m_head  ;
  TrainCar *newCar = new TrainCar( TrainCar::CoachClass ) ;

  if (m_head -> m_next == NULL) {
    m_head -> m_next = newCar ;
  }// end if for no train

  else {
    //go to the end of locomotives
    while ( ( travPtr -> m_next != NULL ) &&
	    ( travPtr -> m_next -> getType() == TrainCar::Locomotive ) )
      {
        travPtr = travPtr -> m_next;
      }// end while

    if ( hasCar ( TrainCar::BusinessClass ) )
      {
        //go the end of the business cars
        while ( ( travPtr -> m_next != NULL ) &&
		( travPtr -> m_next -> getType() == TrainCar::BusinessClass ) )
          {
            travPtr = travPtr -> m_next;
          }// end while
      }//end go to end of business cars

      // insert new train car
      newCar -> m_next = travPtr -> m_next ;
      travPtr -> m_next = newCar ;
  }//end else

  if ( hasCar ( TrainCar::SnackCar ) )
    {
      removeCar( TrainCar::SnackCar );
      addCar( TrainCar::SnackCar );
    }//end moving snack car
}//end insert CoachClass





/******************************************************************
 *                                                                *
 * Name:          insertSleepingCar                               *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - if this is the first sleeper car, adds a      *
 *                  dining car                                    *
 *                - goes to the end of the train, and adds the    *
 *                  sleeper car                                   *
 *                                                                *
 *****************************************************************/

void Train::insertSleepingCar() 
{
  TrainCar *travPtr = m_head ;
  TrainCar *newCar = new TrainCar( TrainCar::SleepingCar ) ;
  bool firstSleepingCar = false ;

  if ( hasCar(TrainCar::SleepingCar ) != true )
    {       
      firstSleepingCar = true ;
    }

  if (m_head -> m_next == NULL) 
    {
      m_head -> m_next = newCar ;
    }// end if for no train
  else
    {
      //find the last car in the list
      while ( ( travPtr -> m_next != NULL ) )
	{
	  travPtr = travPtr -> m_next;
	}// end while
      
      // insert new train car
      newCar -> m_next = travPtr -> m_next ;
      travPtr -> m_next = newCar ;
    }// end else

  if ( firstSleepingCar )
    {
      insertDiningCar() ;
    }
  
}//end insert sleeping car





/******************************************************************
 *                                                                *
 * Name:          insertDiningCar                                 *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - goes to the start of the sleepers, and adds   *
 *                  the dining car                                *
 *                                                                *
 *****************************************************************/

void Train::insertDiningCar()
{
  TrainCar *travPtr = m_head ;
  TrainCar *newCar = new TrainCar( TrainCar::DiningCar ) ;

  if ( hasCar( TrainCar::SleepingCar ) )
    {       
      while ( ( travPtr -> m_next != NULL ) &&
	      ( travPtr -> m_next -> getType() != TrainCar::SleepingCar ) )
	{
	  travPtr = travPtr -> m_next;
	}// end while
      
      // insert new train car
      newCar -> m_next = travPtr -> m_next ;
      travPtr -> m_next = newCar ;
    }//end if
}//end insert DiningCar





/******************************************************************
 *                                                                *
 * Name:          insertSnackCar                                  *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - if there is a business and snack car then     *
 *                  a snack car is added between them             *
 *                  otherwise the snack car is added in the       *
 *                  middle of the coach cars, favoring the        *
 *                  locomotive side if odd                        *
 *                                                                *
 *****************************************************************/

void Train::insertSnackCar()
{
  TrainCar *travPtr = m_head ;
  TrainCar *newCar = new TrainCar( TrainCar::SnackCar ) ;

  if ( hasCar( TrainCar::SnackCar )!= true) 
    {
      if ( hasCar( TrainCar::BusinessClass ) &&
	   hasCar( TrainCar::CoachClass ) )
	{
	  //go the end of the business cars
	  while ( ( travPtr -> m_next != NULL ) &&
		  ( travPtr -> m_next -> getType() != TrainCar::CoachClass ) )
	    {
	      travPtr = travPtr -> m_next;
	    }// end while
	  
	  // insert new train car
	  newCar -> m_next = travPtr -> m_next ;
	  travPtr -> m_next = newCar ;
	}
      
      else if ( hasCar( TrainCar::CoachClass ) )
	{
	  //count coach cars
	  int coachCount = 0 ;
	  //number of coachs to go into train before adding car
	  int coachOffset = 0;
	  //count coaches
	  while ( ( travPtr != NULL ) )
	    {
	      if ( travPtr -> getType() == TrainCar::CoachClass )
		{
		  coachCount++ ;
		}
	      travPtr = travPtr -> m_next;
	    }
	  //odd coach count
	  if ( coachCount % 2 == 1 ) 
	    {
	      coachOffset = ( coachCount - 1 ) / 2 ;
	    }
	  //even coach count
	  else if ( coachCount % 2 == 0 )
	    {
	      coachOffset = coachCount / 2 ;
	    }
	  
	  //reset travPtr
	  travPtr = m_head ;
	  
	  //go the start of Coach class cars
	  while ( ( travPtr -> m_next -> getType() != TrainCar::CoachClass ) )
	    {
	      travPtr = travPtr -> m_next;
	    }// end while
	  
	  //offsetcoach cars by required amount to get to middle, favoring locomotives
	  int i = 0;
	  while ( i < coachOffset )
	    {
	      travPtr = travPtr -> m_next;
	      i++;
	    }
	  
	  // insert new train car
	  newCar -> m_next = travPtr -> m_next ;
	  travPtr -> m_next = newCar ;
	}//end else if 
    }//end if has snack car is false
}//end insertSnackCar





  /******************************************************************
   *                                                                *
   * Name:          hasCar                                          *
   *                                                                *
   * PreCondition:  valid car type is passed in and train exists    *
   *                                                                *
   * PostCondition: - cycles through train and returns true if      *
   *                  there is a car of the requested type present  *
   *                                                                *
   *****************************************************************/

bool Train::hasCar( TrainCar::cType car ) 
{
  bool hasCar = false;
  TrainCar *travPtr = m_head;

  while ( ( travPtr != NULL ) )
    {
      if ( travPtr -> getType() == car )
	{
	  hasCar = true;
	}
      travPtr = travPtr -> m_next;
    }

  return hasCar;
}





/******************************************************************
 *                                                                *
 * Name:          removeCar                                       *
 *                                                                *
 * PreCondition:  valid car type is passed in and train exists    *
 *                                                                *
 * PostCondition: - for dining cars, all sleepers are removed,    *
 *                  then dining car                               *
 *                - for sleeping car, if the last sleeping car,   *
 *                  a dining car is removed                       *
 *                - for coach and business cars check if there is *
 *                  a snack car, if there is, delete and read     *
 *                - locomotive is removed and snack car is        *
 *                  removed                                       * 
 *                                                                *
 *****************************************************************/

bool Train::removeCar( TrainCar::cType car )
{
  TrainCar *tempPtr = m_head;
  TrainCar *travPtr = m_head;

  if ( car == TrainCar::DiningCar )
    {
      //delete sleeping cars until they are gone
      while ( hasCar ( TrainCar::SleepingCar ) )
	{
	  removeCar ( TrainCar::SleepingCar ) ;
	  //last sleeping car removed deletes dining car
	}
    }
  else if ( car == TrainCar::SleepingCar )
    {
      if ( hasCar ( TrainCar::SleepingCar ) )
	{
	  //train of only sleepercar
	  if ( travPtr -> m_next -> m_next == NULL )
	    {
	      tempPtr = travPtr -> m_next;
	      delete tempPtr;
	      travPtr -> m_next = NULL ;
	    }
	  //if it has several sleepers
	  else if ( travPtr -> m_next -> m_next != NULL )
	    {
	      //find second to last SleepingCar
	      while ( ( travPtr -> m_next -> m_next != NULL ) )
		{
		  travPtr = travPtr -> m_next;
		}	  
	      
	      // delete sleepingCar
	      tempPtr = travPtr -> m_next ;
	      travPtr -> m_next = travPtr -> m_next -> m_next ;
	      delete tempPtr ;
	      
	      //if last sleeping car, remove dining car
	      if ( hasCar ( TrainCar::SleepingCar )  != true )
		{
		  //find dining
		  travPtr = m_head ;
		  while ( ( travPtr -> m_next != NULL ) &&
			  ( travPtr -> m_next -> m_next != NULL ) && 
			  ( travPtr -> m_next -> getType() != TrainCar::DiningCar ) )
		    {
		      travPtr = travPtr -> m_next;
		    }	  
		  // delete diningCar
		  tempPtr = travPtr -> m_next;
		  delete tempPtr;
		  travPtr -> m_next = NULL ;
		}//end if
	    }//end else if
	  return true;
	}
      else 
	{
	  return false;
	}      
      //remove sleeping car
      //check if last sleeping car, if so remove dining car
    }
  else if ( car == TrainCar::BusinessClass )
    {
      if ( hasCar ( TrainCar::BusinessClass ) )
	{
	  //find first business class
	  while ( ( travPtr -> m_next != NULL ) &&
		  ( travPtr -> m_next -> getType() != TrainCar::BusinessClass ) )
	    {
	      travPtr = travPtr -> m_next;
	    }	  

	  // delete busines class
	  tempPtr = travPtr -> m_next ;
	  travPtr -> m_next = travPtr -> m_next -> m_next ;
	  delete tempPtr ;

	  
	  //only move a snack car if there are no more business classes
	  if ( hasCar ( TrainCar::BusinessClass )  != true )
	    {
	      // delete snack car to reposition
	      removeCar ( TrainCar::SnackCar ) ;
	      addCar ( TrainCar::SnackCar ) ;
	    }
	  return true;
	}
      else 
	{
	  return false;
	}      
    }
  else if ( car == TrainCar::CoachClass )
    {
      if ( hasCar ( TrainCar::CoachClass ) )
	{
	  //find first coach class
	  while ( ( travPtr -> m_next != NULL ) &&
		  ( travPtr -> m_next -> getType() != TrainCar::CoachClass ) )
	    {
	      travPtr = travPtr -> m_next;
	    }	  

	  // delete coach class
	  tempPtr = travPtr -> m_next ;
	  travPtr -> m_next = travPtr -> m_next -> m_next ;
	  delete tempPtr ;
	  
	  // delete snack car to reposition
	  removeCar ( TrainCar::SnackCar ) ;
	  
	  //only add another snack car if there is still a coach class per rules
	  if ( hasCar ( TrainCar::CoachClass ) )
	    {
	      addCar ( TrainCar::SnackCar ) ;
	    }
	  return true;
	}
      else 
	{
	  return false;
	}      
    }
  else if ( car == TrainCar::Locomotive )
    {
      if ( hasCar ( TrainCar::Locomotive ) )
	{
	  //delete first locomotive
	  tempPtr = m_head -> m_next ;
	  m_head -> m_next = m_head -> m_next -> m_next ;
	  delete tempPtr ;
	  return true;
	}
      else 
	{
	  return false;
	}
    }

  else if ( car == TrainCar::SnackCar )
    {
      if ( hasCar ( TrainCar::SnackCar ) )
	{
	  //go to car before snack car
	  while ( ( travPtr -> m_next != NULL ) &&
		  ( travPtr -> m_next -> getType() != TrainCar::SnackCar ) )
	    {
	      travPtr = travPtr -> m_next;
	    }	  

	  //delete snack car
	  tempPtr = travPtr -> m_next ;
	  travPtr -> m_next = travPtr -> m_next -> m_next ;
	  delete tempPtr ;
	  return true;
	}
      else 
	{
	  return false;
	}      
    }
  return false;
}// end removeCar





/******************************************************************
 *                                                                *
 * Name:          getNumber                                       *
 *                                                                *
 * PreCondition:  valid m_number and train exists                 *
 *                                                                *
 * PostCondition: - returns train number                          *
 *                                                                *
 *****************************************************************/

int Train::getNumber() const
{
  return m_number;
}





/******************************************************************
 *                                                                *
 * Name:          setNumber                                       *
 *                                                                *
 * PreCondition:  valid num and train exists                      *
 *                                                                *
 * PostCondition: - sets train number                             *
 *                                                                *
 *****************************************************************/

void Train::setNumber( int num ) 
{
  m_number = num;
}





/******************************************************************
 *                                                                *
 * Name:          getNumber                                       *
 *                                                                *
 * PreCondition:  valid m_number and train exists                 *
 *                                                                *
 * PostCondition: - returns train number                          *
 *                                                                *
 *****************************************************************/

Time Train::getDepartureTime() const
{
  return m_departs;
}





/******************************************************************
 *                                                                *
 * Name:          setDepartureTime                                *
 *                                                                *
 * PreCondition:  valid t and train exists                        *
 *                                                                *
 * PostCondition: - sets departure time                           *
 *                                                                *
 *****************************************************************/

void Train::setDepartureTime( const Time& t )
{
  m_departs = t;
}





/******************************************************************
 *                                                                *
 * Name:          getDestination                                  *
 *                                                                *
 * PreCondition:  valid m_destination and train exists            *
 *                                                                *
 * PostCondition: - returns train destination                     *
 *                                                                *
 *****************************************************************/

string Train::getDestination() const
{
  return m_destination;
}





/******************************************************************
 *                                                                *
 * Name:          setDestination                                  *
 *                                                                *
 * PreCondition:  valid dest and train exists                     *
 *                                                                *
 * PostCondition: - sets train destination                        *
 *                                                                *
 *****************************************************************/

void Train::setDestination ( string dest )
{
  m_destination = dest;
}





/******************************************************************
 *                                                                *
 * Name:          isvalid                                         *
 *                                                                *
 * PreCondition:  train exists                                    *
 *                                                                *
 * PostCondition: - if train has a locomotive and coach returns   *
 *                  true, otherwise false                         *
 *                                                                *
 *****************************************************************/

bool Train::isValid()
{
  if ( hasCar(TrainCar::Locomotive) && hasCar(TrainCar::CoachClass) )
    {
      return true;
    }

  return false;
}

