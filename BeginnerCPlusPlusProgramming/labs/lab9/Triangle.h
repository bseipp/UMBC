#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape
{
 public: 
  Triangle(int length = 0, int height = 0);
  virtual int GetArea() const;
  virtual void Draw() const;
  virtual ~Triangle();

 private:
  int m_length, m_height;
};

#endif
