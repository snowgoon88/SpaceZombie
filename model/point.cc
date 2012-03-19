// -*- coding: utf-8 -*-

#include "point.h"

#include <sstream>
#include <iostream>

unsigned int PhyPoint::_nb_points = 0;
State PhyPoint::s_NONE    ( 0, "NONE");
State PhyPoint::s_CONTACT ( 1, "CONTACT");
State PhyPoint::s_FALL    ( 2, "FALL");
State PhyPoint::s_VOID    ( 3, "VOID");
// *****************************************************************************
PhyPoint::PhyPoint( float x, float y, float z, float vx, float vy, float vz ) : 
  _player_state( s_NONE ), 
  _curr_cell()
{
  _id = _nb_points;
  _nb_points++;
  _x = x; _y = y; _z = z;
  _vx = vx; _vy = vy; _vz = vz;

  _fg_contact = false;
}
PhyPoint::PhyPoint( PhyPoint& other_p ) :
  _player_state( other_p._player_state ),
  _curr_cell( other_p._curr_cell )
{
  _id = _nb_points;
  _nb_points++;
  _x = other_p._x;
  _y = other_p._y;
  _z = other_p._z;
  _vx = other_p._vx;
  _vy = other_p._vy;
  _vz = other_p._vz;

  _fg_contact = other_p._fg_contact;
}
PhyPoint::~PhyPoint(void)
{
}
// *****************************************************************************
std::string PhyPoint::repr_dump()
{
  std::stringstream ss;
  ss << "PhyPoint_" << _id << " ( " << _x << ", " << _y << ", " << _z << ")";
  ss << " ( " << _vx << ", " << _vy << ", " << _vz << ") c=" << _fg_contact << " s=" << _player_state._name;

  return ss.str();
}
// *****************************************************************************
void PhyPoint::get_future_pos( double ms, float& x, float& y, float& z)
{
  x = _x + ms * _vx / 1000.0;
  y = _y + ms * _vy / 1000.0;
  z = _z + ms * _vz / 1000.0;
}
void PhyPoint::apply_force( double ms, float fx, float fy, float fz)
{
  std::cout << "PhyPoint::apply_force fx=" << fx << ", fy=" << fy << ", fz=" << fz << "\n";
  _vx = _vx + ms * fx / 1000.0;
  _vy = _vy + ms * fy / 1000.0;
  _vz = _vz + ms * fz / 1000.0;
}
// *****************************************************************************
