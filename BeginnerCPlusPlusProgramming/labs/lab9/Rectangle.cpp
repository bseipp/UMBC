#include "Rectangle.h"
#include "Shape.h"
#include <iostream>

using namespace std;

Rectangle::Rectangle(int l, int w)
{ 
  m_length = l;
  m_width = w;
}

int Rectangle::GetArea() const
{
  return m_length * m_width;
}

void Rectangle::Draw() const
{
  cout << "Drawing Rectangle" << endl << endl;
}

Rectangle::~Rectangle()
{
}
