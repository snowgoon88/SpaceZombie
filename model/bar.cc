// -*- coding: utf-8 -*-

#include "bar.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
Bar::Bar(TVec3 ori, TVec3 dir, float x_start, float x_end, float thick)
  : Model()
{
  _ori = ori;
  _dir = dir.normalized();
  _x_start = x_start;
  _x_end = x_end;

  get_point_at( _x_start, _pt_start );
  get_point_at( _x_end, _pt_end );
  notify_observers();
}
/** Destruction */
Bar::~Bar()
{
}
//*********************************************************************** STRING
std::string Bar::dump_string()
{
  std::stringstream ss;

  ss << "Bar ori=" << line_repr(_ori) << " dir=" << line_repr(_dir) << " start=" << line_repr(_pt_start) << " (" << _x_start << ") " << " end=" << line_repr(_pt_end) << " (" << _x_end << ")";
  
  return ss.str();
}
//************************************************************************** SET
void Bar::set_position( TVec3 pos ) 
{
  _ori = pos;
  get_point_at( _x_start, _pt_start );
  get_point_at( _x_end, _pt_end );
  notify_observers();
}
void Bar::set_dir( TVec3 dir )
{
  _dir = dir.normalized();
  get_point_at( _x_start, _pt_start );
  get_point_at( _x_end, _pt_end );
  notify_observers();
}
//******************************************************************** GET_POINT
bool Bar::get_point_at( float x_coord, TVec3& point ) 
{
  if( (x_coord >= _x_start) and (x_coord <= _x_end) ) {
    point = _ori + x_coord * _dir;
    return true;
  }
  return false;
}
//******************************************************************************
