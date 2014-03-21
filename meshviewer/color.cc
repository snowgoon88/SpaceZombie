// -*- coding: utf-8 -*-

#include "color.h"

//********************************************************************* CREATION
/** Creation */
TColorF::TColorF()
{
  _red = _green = _blue = _alpha = 0.0f;
}
TColorF::TColorF(float red, float green, float blue, float alpha)
{
  _red = red;
  _green= green;
  _blue = blue;
  _alpha = alpha;
}
/* template<typename T> */
/* TColor<T>::TColor( char * address ) */
/* { */
/*   unsigned int size_T = sizeof(T); */
/*   memcpy( &_red, &(address[0]), size_T); */
/*   memcpy( &_green, &(address[0+size_T]), size_T); */
/*   memcpy( &_blue, &(address[0+size_T*2]), size_T); */
/*   memcpy( &_alpha, &(address[0+size_T*3]), size_T); */
/* } */
/** Destruction */
TColorF::~TColorF()
{
}
//*********************************************************************** STRING
std::string TColorF::str_dump()
{
  std::stringstream ss;
  
  ss << SETPREC(2) << r();
  ss << ", " << SETPREC(2) << g();
  ss << ", " << SETPREC(2) << b();
  ss << ", " << SETPREC(2) << a();

  return ss.str();
}
//******************************************************************************
