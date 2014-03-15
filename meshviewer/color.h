/* -*- coding: utf-8 -*- */

#ifndef __Color_H__
#define __Color_H__

#include<string>
#include <iostream>
#include <sstream>

/**
 * Abstract color, read from memory, can get
 * red(), green(), blue(), alpha() as int.
 */
class IColor
{
  /** Creation from memory */
  virtual int r() = 0;
  virtual int g() = 0;
  virtual int b() = 0;
  virtual int a() = 0;

  /** display string */
  std::string str_dump() { return "IColor is Abstract !!"; };
};
/**
 * Une couleur a 4 variables : r,g,b et a.
 */
template<typename T>
class TColor : public IColor
{
protected:
  T red;
  T green;
  T blue;
  T alpha;
public:
  
  /** Creation */
  TColor();
  /** Creation from array of char */
  TColor( char * address );
  /** Destruction */
  virtual ~TColor();
  
  /** display string */
  std::string str_dump();

  /** get various variables of color */
  int r() {return (int) red;};
  int g() {return (int) green;};
  int b() {return (int) blue;};
  int a() {return (int) alpha;};
};
//********************************************************************* CREATION
/** Creation */
template<typename T>
TColor<T>::TColor()
{
  red = green = blue = alpha = 0;
}
template<typename T>
TColor<T>::TColor( char * address )
{
  unsigned int size_T = sizeof(T);
  memcpy( &red, &(address[0]), size_T);
  memcpy( &green, &(address[0+size_T]), size_T);
  memcpy( &blue, &(address[0+size_T*2]), size_T);
  memcpy( &alpha, &(address[0+size_T*3]), size_T);
}
/** Destruction */
template<typename T>
TColor<T>::~TColor()
{
}
//*********************************************************************** STRING
template<typename T>
std::string TColor<T>::str_dump()
{
  std::stringstream ss;
  
  ss << r() << ", " << g() << ", " << b() << ", " << a();
  return ss.str();
}
//******************************************************************************

#endif // __Color_H__
