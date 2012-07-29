// -*- coding: utf-8 -*-

#include "point.h"

#include <sstream>
#include <iostream>

unsigned int PhyPoint::_nb_points = 0;
State PhyPoint::s_NONE    ( 0, "NONE");
State PhyPoint::s_CONTACT ( 1, "CONTACT");
State PhyPoint::s_FALL    ( 2, "FALL");
State PhyPoint::s_VOID    ( 3, "VOID");
// ********************************************************************** CREATE
PhyPoint::PhyPoint( TVec3 pos, TVec3 speed ) : 
  _state( s_NONE ), 
  _curr_cell()
{
  _id = _nb_points;
  _nb_points++;
  _pos = pos;
  _speed = speed;

  _fg_contact = false;
}
PhyPoint::PhyPoint( float x, float y, float z, float vx, float vy, float vz ) : 
  _pos(x,y,z), _speed(vx,vy,vz),
  _state( s_NONE ), 
  _curr_cell()
{
  _id = _nb_points;
  _nb_points++;

  _fg_contact = false;
}
PhyPoint::PhyPoint( PhyPoint& other_p ) :
  _state( other_p._state ),
  _curr_cell( other_p._curr_cell )
{
  _id = _nb_points;
  _nb_points++;

  _pos = other_p._pos;
  _speed = other_p._speed;

  _fg_contact = other_p._fg_contact;
}
PhyPoint::~PhyPoint(void)
{
}
// ************************************************************************ DUMP
std::string PhyPoint::dump_str()
{
  std::stringstream ss;
  ss << "PhyPoint_" << _id << " ( " << line_repr(_pos)[0] << ")";
  ss << " ( " << line_repr(_speed) << ") c=" << _fg_contact << " s=" << _state._name;

  return ss.str();
}
// ********************************************************************** FUTURE
TVec3 PhyPoint::get_future_pos( double ms )
{
  TVec3 new_pos = _pos + ms * _speed / 1000.0;
  return new_pos;
}
// void PhyPoint::apply_force( double ms, float fx, float fy, float fz)
// {
//   std::cout << "PhyPoint::apply_force fx=" << fx << ", fy=" << fy << ", fz=" << fz << "\n";
//   _vx = _vx + ms * fx / 1000.0;
//   _vy = _vy + ms * fy / 1000.0;
//   _vz = _vz + ms * fz / 1000.0;
// }
// *****************************************************************************
