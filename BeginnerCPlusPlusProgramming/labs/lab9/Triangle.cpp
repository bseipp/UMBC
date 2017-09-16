#include "Triangle.h"
#include "Shape.h"
#include <iostream>

using namespace std;

Triangle::Triangle( int l, int h )
{
  m_length = l;
  m_height = h;
}

int Triangle::GetArea() const
{
  return .5 * m_length * m_height;
}

void Triangle::Draw() const
{
  cout << "Drawing a Triangle. " << endl << endl;
}

Triangle::~Triangle() 
{
}
