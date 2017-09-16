//
// Time.h
//
// CMSC 202 Project File
//

#ifndef TIME_H
#define TIME_H


class Time {
 public:

  //Constructors
  Time() ;
  Time(int h, int m) ;
  friend ostream& operator<<(ostream &outStream, const Time& t) ;
  friend bool operator<(const Time &t1, const Time &t2) ;
  friend Time operator+(const Time &t, int a) ;

 private:

  int m_hours;
  int m_minutes;
};

#endif
