#include <iostream>
#include "Fraction.h" 
using namespace std;


Fraction::Fraction(int num, int denom){
  m_numerator = num;
  if (denom > 0)
    m_denominator = denom;
  else
    cout << "Denominator is 0. This is invalid." << endl;
}

Fraction::Fraction(){
  m_numerator = 1;
  m_denominator = 1;
}

Fraction Fraction::Reciprocal(){
  Fraction frac(m_denominator, m_numerator);
  return frac;
}

void Fraction::Output(){
  cout << endl << "The fraction is: " << m_numerator << "/" << m_denominator << endl;
}

