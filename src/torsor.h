// -*- coding: utf-8 -*-
#ifndef __TORSOR__H_
#define __TORSOR__H_

#include "utils.h"

#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class Torsor> TorsorPtr;
#else
    typedef class Torsor * TorsorPtr;
#endif

/**
 * A Torsor is given by a Resultante and a Moment.
 */
class Torsor 
{
 public:
  /** Default creation */
  Torsor( TVec3 res=TVec3(0,0,0), TVec3 mom=TVec3(0,0,0), TVec3 point=TVec3(0,0,0) );
  /** Copy creation */
  Torsor( const Torsor& t );
  /** Destructor */
  ~Torsor();

  /** Display */
  std::string display_str( int precision=3 ) const;

  /** Apply torsor at a point */
  TVec3 apply( const TVec3& point ); 
  /** Reduce torsor at another point */
  Torsor& reduce_at( const TVec3& point );

  /** Various operators */
  Torsor& operator=( const Torsor& t);
  Torsor operator+( const Torsor& t);
  Torsor operator-( const Torsor& t);
  Torsor operator*( const float val);


  /** Co-moment */
  float comoment( const Torsor& t);
  float automoment();
  /** Get one point of the central axis (vector I->_p) , or (0,0,0) if _r is null */
  TVec3 get_Ip();
  
 public:
  /** Resultant */
  TVec3 _r;
  /** Moment */
  TVec3 _m;
  /** Point */
  TVec3 _p;
};
#endif // __TORSOR__H_
