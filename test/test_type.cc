/* -*- coding: utf-8 -*- */
// if (typeid(a) == typeid(int))
// //do stuff
// voir aussi std::numeric_limits

#include <typeinfo>
#include <iostream>
#include <limits>       // std::numeric_limits

// on peut l'appeler sans préciser test_type<int> car le type
// int sera déterminé par l'argument. Magique non?
template<typename T>
void test_type(T v)
{
  int tmp = v;

  if (typeid(v) == typeid(unsigned char)) {
    std::cout << "unsigned char\n";
  }
  if (typeid(v) == typeid(char)) {
    std::cout << "char\n";
  }
  if (typeid(v) == typeid(unsigned short)) {
    std::cout << "unsigned short\n";
  }
  if (typeid(v) == typeid(short)) {
    std::cout << "short\n";
  }
  std::cout << "between " << (int)std::numeric_limits<T>::min() << " and ";
  std::cout << (int)std::numeric_limits<T>::max() << "\n";

  std::cout << "ori=" << v << ", as int=" << tmp << ", cast=" << (int) v << "\n";
}

//******************************************************************************
int main( int argc, char *argv[] )
{
  unsigned char v_uc = 130;
  char v_c = -24;
  unsigned short v_us = 23;
  short v_s = -12;
  unsigned int v_ui = 341527;
  int v_i= -123456;

  test_type(v_uc);
  test_type(v_c);
  test_type(v_us);
  test_type(v_s);
  test_type(v_ui);
  test_type(v_i);

  return 0;
}
