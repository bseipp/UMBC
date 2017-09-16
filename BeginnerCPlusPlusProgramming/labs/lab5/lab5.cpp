#include <iostream>
#include "Complex.h"
using namespace std;

int main() {

  Complex a(3,2);
  Complex b(1,2);
  Complex c(4,5);
  
  Complex ab(a.Multiply(b));
  cout << ab.ToString() << endl;
  
  Complex cTimesTwo(c.Multiply(2.0));
  cout << cTimesTwo.ToString() << endl;
  

  // To test your code, you must
  // - create at least three Complex numbers using
  //   the non-default constructor.
  // - Use the Multiply() function to compute the
  //   product of two Complex numbers; output the
  //   product using the ToString() function.
  // - Use the Multiply function to compute the 
  //   product of a Complex number and a double; 
  //   output the product using the ToString()
  //   function.

  return 0;
}
  
