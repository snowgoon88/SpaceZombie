// -*- coding: utf-8 -*-
// 
// test output format in C++ (from http://www.arachnoid.com/cpptutor/student3.html)
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip> // setw, setprecision

void test_width()
{
  std::cout << "@@@ WIDTH --------------------\n";
  const int max = 12;
  const int width = 6;
  for(int row = 1;row <= max;row++) {
    for(int col = 1;col <= max;col++) {
      std::cout << std::setw(width) << row * col;
    }
    std::cout << std::endl;
  }
}
void test_precision()
{
  std::cout << "@@@ PRECISION ----------------\n";
  double x = 800000.0/81.0;
  std::cout << std::setprecision(2) << x;
  std::cout << std::endl;
}
void test_precision_fixed()
{
  std::cout << "@@@ PRECISION FIXED ----------\n";

  double x = 800000.0/81.0;
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) << x;
  std::cout << std::endl;
}

int main( int argc, char **argv )
{
  test_width();
  test_precision();
  test_precision_fixed();

  return 0;
}
