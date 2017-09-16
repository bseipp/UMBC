#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape
{
 public:
  Rectangle(int length = 0, int width = 0);
  virtual int GetArea() const;
  virtual void Draw() const;
  virtual ~Rectangle();

 private:
  int m_length, m_width;
};

#endif
