#include "Shape.h"
#include <iostream>
using namespace std;

Shape::~Shape()
{
// no code
}

void Shape::Draw() const
{
  cout << "Shape Drawn." << endl << endl;
}
