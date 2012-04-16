// -*- coding: utf-8 -*-

#include "torsor.h"

/******************************************************************* CREATION */
/** Default creation */
Torsor::Torsor( TVec3 res, TVec3 mom, TVec3 point )
{
  _r = res;
  _m = mom;
  _p = point;
}
/** Copy creation */
Torsor::Torsor( const Torsor& t )
{
  _r = t._r;
  _m = t._m;
  _p = t._p;
}
/** Destructor */
Torsor::~Torsor()
{
}
/******************************************************************** DISPLAY */
/** Display */
std::string Torsor::display_str( int precision ) const
{
  std::stringstream ss;
  ss << "{ " << line_repr( _r, precision ) << " / ";
  ss << line_repr( _m, precision ) << "} ";
  ss << "at " << line_repr( _p, precision );

  return ss.str();
}
/********************************************************************** APPLY */
TVec3 Torsor::apply( const TVec3& point )
{
  TVec3 res = _m + (_p - point).cross( _r );
  return res;
}
Torsor& Torsor::reduce_at( const TVec3& point )
{
  _m = apply( point );
  _p = point;
  return *this;
}
/******************************************************************* OPERATOR */
Torsor& Torsor::operator=( const Torsor& t)
{
  _r = t._r;
  _m = t._m;
  _p = t._p;
  return *this;
}
Torsor Torsor::operator+( const Torsor& t)
{
  // Check same reduction point.
  if( _p != t._p ) {
    std::cerr << "Torsor::operator+ : different reduction points\n";
    std::cerr << "this = " << display_str() << "\n";
    std::cerr << "right= " << t.display_str() << "\n";
    return Torsor();
  }
  Torsor result( _r+t._r, _m+t._m, _p);
  return result;
}
Torsor Torsor::operator-( const Torsor& t)
{
  // @todo Check same reduction point.
  if( _p != t._p ) {
    std::cerr << "Torsor::operator- : different reduction points\n";
    std::cerr << "this = " << display_str() << "\n";
    std::cerr << "right= " << t.display_str() << "\n";
    return Torsor();
  }
  Torsor result( _r-t._r, _m-t._m, _p);
  return result;
}
Torsor Torsor::operator*( const float val)
{
  Torsor result( _r * val, _m * val, _p);
  return result;
}
/********************************************************************* MOMENT */
float Torsor::comoment( const Torsor& t)
{
  // @todo Check same reduction point.
  if( _p != t._p ) {
    std::cerr << "Torsor::comoment : different reduction points\n";
    std::cerr << "this = " << display_str() << "\n";
    std::cerr << "right= " << t.display_str() << "\n";
    return 0.0f;
  }
  float cm = _r.dot( t._m ) + t._r.dot( _m );
  return cm;
}
float Torsor::automoment()
{
  return 0.5f * comoment( *this );
}
TVec3 Torsor::get_Ip()
{
  float norm_r = _r.norm();
  if( norm_r > 0.000001 ) {
    TVec3 result = _m.cross( _r ) / (norm_r*norm_r);
    return result;
  }
  return TVec3(0,0,0);
}
/******************************************************************************/
