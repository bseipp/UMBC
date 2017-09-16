#include <iostream>
#include "Fraction.h"

using namespace std;

int main()
{
  int userNumerator;
  int userDenominator;
  cout << "Please enter a Numerator: " << endl;
  cin >> userNumerator;

  cout << endl << "Please enter a Denominator: " << endl;
  cin >> userDenominator;

  Fraction frac1(userNumerator, userDenominator);
  Fraction frac2 = frac1.Reciprocal();
  frac2.Output();

  Fraction frac3;
  frac3.Output();

  Fraction frac4(2, 0);

  // Create 3 fractions:
  //  - Read the first fraction from the keyboard using cin.
  //    Find the reciprocal of this fraction and print it to the screen.
  //  - The second fraction will be created with default values. You
  //    should also print this to the screen.
  //  - Attempt to create a fraction with a denominator of zero, which 
  //    should print an error

  return 0;  
}
