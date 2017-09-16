//
// my_array_driver.cpp : simple driver for the my_array class
//
// Compile with:
//    g++ -Wall -ansi my_array_driver.cpp my_array.cpp -o my_array_driver
//

#include <iostream>
#include "my_array.h"

using namespace std;

int main() {

  my_array x;
  my_array::const_iterator itr;

  // append some values into my_array x
  for (int i = 1; i <= my_array::MAX_SIZE; i++ ) 
    x.push_back( (i*i) % 19 );

  // my_array does not keep items in order
  cout << "my_array x:" << endl;
  for (itr = x.begin(); itr != x.end(); itr++)
    cout << *itr << " ";
  cout << endl << endl;

  // erase a couple items from x and print the result
  // notice that erasing the item at index 2 changes
  // the value at index 7
  int i = 0;
  for (itr = x.begin(); itr != x.end(); itr++) {
    if (i == 2 || i == 7) x.erase(itr);
    i++;
  }
  cout << "my_array x after erasing two entries:" << endl;
  for (itr = x.begin(); itr != x.end(); itr++)
    cout << *itr << " ";
  cout << endl << endl;

  // This code should result in a range_error exception
  cout << "Constructing my_array with too much data "
       << "causes an exception:" << endl;
  try {
    int arr[my_array::MAX_SIZE + 2] = {0};
    my_array y(arr, my_array::MAX_SIZE + 2);
  } catch (exception& e) {
    cerr << "Error: " << e.what() << endl;
  }
  
  return 0;
}
