/* -*- coding: utf-8 -*- */

#ifndef __Color_H__
#define __Color_H__

#include <string>
#include <iostream>
#include <sstream>
#include <climits>               // INT_MAX
#include "utils.h"               // SETPREC(P)
// Smart pointer
#ifdef HAVE_BOOST
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class IColor> IColorPtr;
#else
typedef class IColor * IColorPtr;
#endif

/**
 * Abstract color, read from memory, can get
 * red(), green(), blue(), alpha() as int.
 */
class IColor
{
 public:
  /** Creation from memory */
  virtual int r() = 0;
  virtual int g() = 0;
  virtual int b() = 0;
  virtual int a() = 0;

  /** display string */
  virtual std::string str_dump() { return "IColor is Abstract !!"; };
};
/**
 * Une couleur a 4 variables : r,g,b et a. TOUTES ENTIERES
 */
template<typename T>
class TColor : public IColor
{
protected:
  T _red;
  T _green;
  T _blue;
  T _alpha;
public:
  
  /** Creation */
  TColor();
  /** Creation from 4 values */
  TColor(T red, T green, T blue, T alpha);
  /** Creation from array of char */
  TColor( char * address );
  /** Destruction */
  virtual ~TColor();
  
  /** display string */
  std::string str_dump();

  /** get various variables of color */
  int r() {return (int) _red;};
  int g() {return (int) _green;};
  int b() {return (int) _blue;};
  int a() {return (int) _alpha;};
};
//********************************************************************* CREATION
/** Creation */
template<typename T>
TColor<T>::TColor()
{
  _red = _green = _blue = _alpha = 0;
}
template<typename T>
TColor<T>::TColor(T red, T green, T blue, T alpha)
{
  unsigned int size_T = sizeof(T);
  memcpy( &_red, &(red), size_T);
  memcpy( &_green, &(green), size_T);
  memcpy( &_blue, &(blue), size_T);
  memcpy( &_alpha, &(alpha), size_T);
}
template<typename T>
TColor<T>::TColor( char * address )
{
  unsigned int size_T = sizeof(T);
  memcpy( &_red, &(address[0]), size_T);
  memcpy( &_green, &(address[0+size_T]), size_T);
  memcpy( &_blue, &(address[0+size_T*2]), size_T);
  memcpy( &_alpha, &(address[0+size_T*3]), size_T);
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
/**
 * Une couleur a 4 variables : r,g,b et a. FLOAT
 */
class TColorF : public IColor
{
protected:
  float _red;
  float _green;
  float _blue;
  float _alpha;
public:
  
  /** Creation */
  TColorF();
  /** Creation from 4 values */
  TColorF( float red, float green, float blue, float alpha);
  /** Creation from array of char */
  //TColorF( char * address );
  /** Destruction */
  virtual ~TColorF();
  
  /** display string */
  std::string str_dump();

  /** get various variables of color */
  int r() {float val = _red * INT_MAX; return (int) val;};
  int g() {float val = _green * INT_MAX; return (int) val;};
  int b() {float val = _blue * INT_MAX; return (int) val;};
  int a() {float val = _alpha * INT_MAX; return (int) val;};
};
#endif // __Color_H__
