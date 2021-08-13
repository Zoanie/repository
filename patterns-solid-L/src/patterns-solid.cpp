//============================================================================
// Name        : patterns-solid.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.udemy.com/course/patterns-cplusplus/learn/lecture
//============================================================================

/*
 * Liskov Substitution Principle:    The 'L' in SOLID
 *
 * Objects in a program should be replaceable with instances of their subtypes (derived objects)
 * w/o altering the correctness of the program.
 *
 * This source code sets up an example that breaks this principle and offers a solution.
 */
#include <iostream>
using namespace std;

class Rectangle
{
protected:
  int width, height;
public:
  Rectangle(const int width, const int height)
    : width{width}, height{height} { }

  int get_width() const { return width; }
  virtual void set_width(const int width) { this->width = width; }
  int get_height() const { return height; }
  virtual void set_height(const int height) { this->height = height; }

  int area() const { return width * height; }
  virtual ~Rectangle(){};
};

class Square : public Rectangle
{
public:
  Square(int size): Rectangle(size,size) {}

  /*
   * This method breaks the Liskov substitution principle.
   * It modifies the width and height, when it should only be modifying one attribute.
   */
  void set_width(const int width) override {
    this->width = width;	// height = width;
  }
  void set_height(const int height) override {
    this->height = height;  // width = height;
  }
};

/*
 * This this the offered solution to
 */
struct RectangleFactory
{
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int size);
};

void unitTest(Rectangle& r)
{
  int w = r.get_width();

  r.set_height(10);

  std::cout << "expected area = " << (w * 10)
    << ", got " << r.area() << std::endl;

}

int main()
{
  cout << "https://www.udemy.com/course/patterns-cplusplus/learn/lecture" << endl;

  Rectangle r{ 5,5 };
  unitTest(r);

  Square s{ 5 };
  unitTest(s);

  getchar();
  return 0;
}
