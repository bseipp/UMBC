//
// Time.cpp
//
// CMSC202 Project File


#include <ostream>
#include <iomanip>
#include <iostream>
using namespace std;

#include "Time.h"


Time::Time() 
{
  m_hours = 0 ;
  m_minutes = 0 ;
}//end Time() default constructor



Time::Time( int h, int m )
{
  if ((h > 24) or (h < 0))
    {
      m_hours = 0;
      cout << "Invalid Hours." << endl;
    }// end if 
  else
    m_hours = h ;


  if ((m > 60) or (m < 0))
    {
      m_minutes = 0;
      cout << "Invalid Minutes." << endl;
    }// end if
  else 
    m_minutes = m ;

}//end non-default constructor



ostream& operator<<(ostream& outStream, const Time& t) 
{
  cout.fill('0');
  outStream << setw(2) << t.m_hours << ":" << setw(2) << t.m_minutes;
  return outStream;
}//end operator <<

Time operator+(const Time &t, int a) 
{
  int minutes = t.m_minutes + a ;
  int hours = t.m_hours;

  while ( minutes > 59 ) 
    {
      hours++;
      minutes = minutes - 60 ;
    }//end while

  Time newTime(hours, minutes) ;
  return newTime;
}//end operator +

bool operator<(const Time& t1, const Time& t2) 
{
  if (t1.m_hours > t2.m_hours)
    return false ;
  else if (t1.m_hours == t2.m_hours)
    {
    if (t1.m_minutes > t2.m_minutes)
      return false ;
    }// end else if
  return true ;
}// end operator <
