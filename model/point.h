// -*- coding: utf-8 -*-

#ifndef __PHYPOINT_H__
#define __PHYPOINT_H__

#include <string>
#include "cell.h"
#include "state.h"

// Smart pointer
#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class PhyPoint> PhyPointPtr;
#else
    typedef class PhyPoint * PhyPointPtr;
#endif

#define POINT_MAX_SPEED 10.0
/**
 *
 */
class PhyPoint {
 public:
  //PhyPoint(void);
  PhyPoint( float x=0.0, float y=0.0, float z=0.0, 
	    float vx=0.0, float vy=0.0, float vz=0.0 );
  PhyPoint( PhyPoint& other_c );
  virtual ~PhyPoint(void);

  virtual std::string repr_dump();

  void get_future_pos( double ms, float& x, float& y, float& z);
  void apply_force( double ms, float fx, float fy, float fz);
  /** id */
  unsigned int _id;
  /** Position */
  float _x, _y, _z;
  /** Speed */
  float _vx, _vy, _vz;

  /** Flag if point is in contact to a surface */
  bool _fg_contact;
  State _player_state;
  CellPtr _curr_cell;

  static unsigned int _nb_points;
  static State s_NONE;
  static State s_CONTACT;
  static State s_FALL;
  static State s_VOID;
};

#endif // __PHYPOINT_H__
