// -*- coding: utf-8 -*-

#include "cell.h"
#include "utils.h"

#include <sstream>
#include <iostream>

unsigned int Cell::_nb_cells = 0;
float Cell::size = 0.5;
// *****************************************************************************
// Cell::Cell(void)
// {
//   _id = _nb_cells;
//   _nb_cells++;
//   _x = _y = _z = 0.0;
//   _ang_x = _ang_y = 0.0;
//   for( unsigned int ind_n = 0; ind_n < NB_DIR; ++ind_n ) {
//     _neighbors[ind_n] = NULL;
//     //_sep[ind_n] = NULL;
//   }
// }
Cell::Cell( float x, float y, float z, float ang_x, float ang_y )
{
  _id = _nb_cells;
  _nb_cells++;
  _x = x; _y = y; _z = z;
  _ang_x = ang_x; _ang_y = ang_y;
  for( unsigned int ind_n = 0; ind_n < NB_DIR; ++ind_n ) {
    _neighbors[ind_n] = NULL;
    //_sep[ind_n] = NULL;
  }
}
Cell::Cell( Cell& other_c )
{
  _id = _nb_cells;
  _nb_cells++;
  _x = other_c._x;
  _y = other_c._y;
  _z = other_c._z;
  _ang_x = other_c._ang_x;
  _ang_y = other_c._ang_y;
  for( unsigned int ind_n = 0; ind_n < NB_DIR; ++ind_n ) {
    _neighbors[ind_n] = other_c._neighbors[ind_n];
    //_sep[ind_n] = other_c._sep[ind_n];
  }
}
Cell::~Cell(void)
{
}
// *****************************************************************************
std::string Cell::repr_dump()
{
  std::stringstream ss;
  ss << "Cell_" << _id << " ( " << _x << ", " << _y << ", " << _z << ")";
  ss << " pente=( " << to_deg(_ang_x) << ", " << to_deg(_ang_y) << ")";
  ss << "\n   n=";
  for( unsigned int ind_n = 0; ind_n < NB_DIR; ++ind_n ) {
    if( _neighbors[ind_n] != NULL ) {
      ss << _neighbors[ind_n]->_id << "/";
    }
    else {
      ss << "-/";
    }
  }
  
  return ss.str();
}
// *****************************************************************************
float Cell::get_z_at( float x, float y )
{
  if( _ang_x != 0 ) {
    return _z + (y - _y) * tanf( _ang_x );
  }
  else if( _ang_y != 0 ) {
    return _z + (x - _x) * tanf( _ang_y );
  }
  return _z;
}
// *****************************************************************************
bool Cell::is_leaving_cell( float x, float y, unsigned int& dir )
{
  if( (x > _x+ size) or (x < _x-size ) or
      (y > _y+ size) or (y < _y-size )) {
    dir = get_dir_to( x, y );
    std::cout << "@@@ " << x << ", " << y << " leaves " << repr_dump() << " from " << dir << "\n";
    return true;
  }
  return false;
}
unsigned int Cell::get_dir_to( float x, float y )
{
  if( y > _y and ((y-_y) > -(x-_x) and (y-_y) >= (x-_x)) ) {
    return 0;
  }
  if( x > _x and ((x-_x) > (y-_y) and (x-_x) >= -(y-_y)) ) {
    return 1;
  }
  if( y < _y and ((y-_y) < -(x-_x) and (y-_y) <= (x-_x)) ) {
    return 2;
  }
  if( x < _x and ((x-_x) < (y-_y) and (x-_x) <= -(y-_y)) ) {
    return 3;
  }
  return 0;
}

// bool Cell::has_neigbour( CellPtr other_c )
// {
//   for( unsigned int ind_n = 0; ind_n < NB_DIR; ++ind_n ) {
//     if( _neighbors[ind_n] == other_c ) {
//       return true;
//     }
//   }
//   return false;
// }
// *****************************************************************************
