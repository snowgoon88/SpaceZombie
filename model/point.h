// -*- coding: utf-8 -*-

#ifndef __PHYPOINT_H__
#define __PHYPOINT_H__

#include <string>
#include "utils.h"
#include "cell.h"
#include "state.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class PhyPoint> PhyPointPtr;

#define POINT_MAX_SPEED 10.0
/**
 *
 */
class PhyPoint {
 public:
  PhyPoint( TVec3 pos=TVec3(0.0f,0.0f,0.0f), TVec3 speed=TVec3(0.0f,0.0f,0.0f) );
  PhyPoint( float x, float y, float z, 
	    float vx=0.0, float vy=0.0, float vz=0.0 );
  PhyPoint( PhyPoint& other_c );
  virtual ~PhyPoint(void);

  virtual std::string dump_str();

  TVec3 get_future_pos( double ms );
  //void apply_force( double ms, float fx, float fy, float fz);
  /** id */
  unsigned int _id;
  /** Position */
  TVec3 _pos;
  /** Speed */
  TVec3 _speed;

  /** Flag if point is in contact to a surface */
  bool _fg_contact;
  State _state;
  CellPtr _curr_cell;

 public:  /** Class Variables */
  static unsigned int _nb_points;
  static State s_NONE;
  static State s_CONTACT;
  static State s_FALL;
  static State s_VOID;
};

#endif // __PHYPOINT_H__
