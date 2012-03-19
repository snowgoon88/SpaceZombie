// -*- coding: utf-8 -*-

#include <iostream>
#include <sstream>
#include <math.h>
#include <float.h>

#include "world.h"

// *****************************************************************************
World::World(void) : Model()
{
  _ground = GroundPtr( new Ground );
  _player = PhyPointPtr( new PhyPoint );
}
World::World( World& other_w ) : Model(other_w)
{
  std::cerr << "@@@ World::World( World& other_w )\n";
  _ground = other_w._ground;
  _player = other_w._player;
}
World::~World(void)
{
  delete _ground;
  delete _player;
}
// *****************************************************************************
std::string World::repr_dump()
{
  std::stringstream ss;
  ss << "== The World ==\n";
  ss << _ground->repr_dump();
  ss << "\n---------------\n";
  ss << _player->repr_dump();
  ss << "\n---------------\n";

  return ss.str();
}
// *****************************************************************************
void World::add_new_cell( float x, float y, float z)
{
  CellPtr cell = CellPtr (new Cell);
  cell->_x = x;
  cell->_y = y;
  cell->_z = z;
  _ground->_cells.push_back( cell );

  notify_observers();
}
void World::add_new_room( float x, float y, float z,
			  unsigned int length_x, unsigned int length_y )
{
  std::vector< CellPtr > room;
  // Create all cells, x_row by x_row.
  for( unsigned int ind_y = 0; ind_y < length_y; ++ind_y ) {
    for( unsigned int ind_x = 0; ind_x < length_x; ++ind_x ) {
      CellPtr cell = CellPtr( new Cell(x+ind_x, y+ind_y, z) );
      room.push_back( cell );
    }
  }
  // link
  for( unsigned int ind_y = 0; ind_y < length_y; ++ind_y ) {
    for( unsigned int ind_x = 0; ind_x < length_x; ++ind_x ) {
      if( ind_y < length_y-1 ) { // North
	room[ind_x + ind_y * length_x]->_neighbors[0] = room[ind_x + (ind_y+1) * length_x];
      }
      if( ind_x < length_x-1 ) { // East
	room[ind_x + ind_y * length_x]->_neighbors[1] = room[ind_x + 1 + ind_y * length_x];
      }
      if( ind_y > 0 ) { // South
	room[ind_x + ind_y * length_x]->_neighbors[2] = room[ind_x + (ind_y-1) * length_x];
      }
      if( ind_x > 0 ) { // West
	room[ind_x + ind_y * length_x]->_neighbors[3] = room[ind_x -1 + ind_y * length_x];
      }
    }
  }
  // Then add to ground
  for( unsigned int ind_y = 0; ind_y < length_y; ++ind_y ) {
    for( unsigned int ind_x = 0; ind_x < length_x; ++ind_x ) {
      _ground->_cells.push_back( room[ind_x + ind_y * length_x] );
    }
  }
  
  notify_observers();
}
void World::connect_cells( std::vector< CellPtr > src_cells,
 			   std::vector< CellPtr > des_cells )
{
  // Check same size
  if( src_cells.size() != des_cells.size() ) {
    std::cerr << "@@@[World::connect_cells] src et des de taille differentes\n";
    return;
  }
  // Direction, distance and height between first cells
  CellPtr src_c = src_cells[0];
  CellPtr des_c = des_cells[0];
  int dir = -1;
  float dist = 0.0;
  float height = des_c->_z - src_c->_z;;
  if( (src_c->_y < des_c->_y) and (src_c->_x == des_c->_x) ) { // North
    dir = 0;
    dist = des_c->_y - src_c->_y;
  }    
  if( (src_c->_x < des_c->_x) and (src_c->_y == des_c->_y)) { // East
    dir = 1;
    dist = des_c->_x - src_c->_x;
  }    
  if( (src_c->_y > des_c->_y) and (src_c->_x == des_c->_x)) { // South
    dir = 2; 
    dist = src_c->_y - des_c->_y;
  }    
  if( (src_c->_x > des_c->_x) and (src_c->_y == des_c->_y)) { // West
    dir = 3; 
    dist = src_c->_x - des_c->_x;
  }    
  if( dir == -1 ) {
    std::cerr << "@@@[World::connect_cells] no direction found\n";
    return;
  }
  if( dist < 2.0 ) {
    std::cerr << "@@@[World::connect_cells] dist is too small\n";
    return;
  }
  unsigned int length = (unsigned int) lrintf( dist - 1.0 );
  // Check others
  for( unsigned int ind_c = 1; ind_c < src_cells.size(); ++ind_c ) {
    switch( dir ) {
    case 0: // North
      if( (src_cells[ind_c]->_y + dist != des_cells[ind_c]->_y) 
	  or (src_cells[ind_c]->_x != des_cells[ind_c]->_x)
	  or (src_cells[ind_c]->_z + height != des_cells[ind_c]->_z)) {
	std::cerr << "@@@[World::connect_cells] N dir or dist or height mismatch for cells " << ind_c << "\n";
	std::cerr << "dir=" << dir << ", dist=" << dist << ", height=" << height << "\n";
	std::cerr << "src : " << src_cells[ind_c]->repr_dump() << "\n";
	std::cerr << "des : " << des_cells[ind_c]->repr_dump() << "\n";
	return;
      }
      break;
    case 1: // East
      if( (src_cells[ind_c]->_x + dist != des_cells[ind_c]->_x) 
	  or (src_cells[ind_c]->_y != des_cells[ind_c]->_y)
	  or (src_cells[ind_c]->_z + height != des_cells[ind_c]->_z)) {
	std::cerr << "@@@[World::connect_cells] E dir or dist or height mismatch for cells " << ind_c << "\n";
	std::cerr << "dir=" << dir << ", dist=" << dist << ", height=" << height << "\n";
	std::cerr << "src : " << src_cells[ind_c]->repr_dump() << "\n";
	std::cerr << "des : " << des_cells[ind_c]->repr_dump() << "\n";
	return;
      }
      break;
    case 2: // South
      if( (src_cells[ind_c]->_y - dist != des_cells[ind_c]->_y) 
	  or (src_cells[ind_c]->_x != des_cells[ind_c]->_x)
	  or (src_cells[ind_c]->_z + height != des_cells[ind_c]->_z)) {
	std::cerr << "@@@[World::connect_cells] S dir or dist or height mismatch for cells " << ind_c << "\n";
	std::cerr << "dir=" << dir << ", dist=" << dist << ", height=" << height << "\n";
	std::cerr << "src : " << src_cells[ind_c]->repr_dump() << "\n";
	std::cerr << "des : " << des_cells[ind_c]->repr_dump() << "\n";
	return;
      }
      break;
    case 3: // West
      if( (src_cells[ind_c]->_x - dist != des_cells[ind_c]->_x) 
	  or (src_cells[ind_c]->_y != des_cells[ind_c]->_y)
	  or (src_cells[ind_c]->_z + height != des_cells[ind_c]->_z)) {
	std::cerr << "@@@[World::connect_cells] W dir or dist or height mismatch for cells " << ind_c << "\n";
	std::cerr << "dir=" << dir << ", dist=" << dist << ", height=" << height << "\n";
	std::cerr << "src : " << src_cells[ind_c]->repr_dump() << "\n";
	std::cerr << "des : " << des_cells[ind_c]->repr_dump() << "\n";
	return;
      }
      break;
    }
  }
  // Build cells
  CellPtr cell;
  std::vector< CellPtr > path;
  float ang = atan2f( height, dist - 1.0 );  
  std::cout << "[World::connect] dir=" << dir << ", length=" << length << ", height =" << height << ", ang=" << ang << "\n";

  switch( dir ) {
  case 0 : // North
    // width of corridor
    for( unsigned int ind_c = 0; ind_c < src_cells.size(); ++ind_c ) {
      // length of path
      for( unsigned int ind_p = 0; ind_p < length; ++ind_p ) {
	cell = CellPtr( new Cell( src_cells[ind_c]->_y + ind_p + 1.0,
				  src_cells[ind_c]->_x,
				  src_cells[ind_c]->_z + (0.5+ind_p) * height / (dist-1),
				  ang, 0.0 ));
	// link along path
	if( ind_p == 0 ) { //link to src if start
	  src_cells[ind_c]->_neighbors[0] = cell;
	  cell->_neighbors[2] = src_cells[ind_c];
	}
	else if( ind_p == length-1 ) { // link to des and previous
	  des_cells[ind_c]->_neighbors[2] = cell;
	  cell->_neighbors[0] = des_cells[ind_c];
	  cell->_neighbors[2] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[0] = cell;
	}
	else { // link to previous
	  cell->_neighbors[2] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[0] = cell;
	}
	// link to preceding "row" in path
	if( ind_c > 0 ) {
	  cell->_neighbors[1] = path[(ind_c-1)*length+ind_p];
	  path[(ind_c-1)*length+ind_p]->_neighbors[3] = cell;
	}
	path.push_back( cell );
      }
    }
    break;
  case 1 : // East
    // width of corridor
    for( unsigned int ind_c = 0; ind_c < src_cells.size(); ++ind_c ) {
      // length of path
      for( unsigned int ind_p = 0; ind_p < length; ++ind_p ) {
	cell = CellPtr( new Cell( src_cells[ind_c]->_x + ind_p + 1.0,
				  src_cells[ind_c]->_y,
				  src_cells[ind_c]->_z + (0.5+ind_p) * height / (dist-1),
				  0.0, ang ));
	// link along path
	if( ind_p == 0 ) { // link to src if start
	  src_cells[ind_c]->_neighbors[1] = cell;
	  cell->_neighbors[3] = src_cells[ind_c];
	}
	else if( ind_p == length-1 ) { // link to des and previous
	  des_cells[ind_c]->_neighbors[3] = cell;
	  cell->_neighbors[1] = des_cells[ind_c];
	  cell->_neighbors[3] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[1] = cell;
	}
	else { // link to previous
	  cell->_neighbors[3] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[1] = cell;
	}
	// link to preceding "row" in path
	if( ind_c > 0 ) {
	  cell->_neighbors[2] = path[(ind_c-1)*length+ind_p];
	  path[(ind_c-1)*length+ind_p]->_neighbors[0] = cell;
	}
	path.push_back( cell );
      }
    }
    break;
  case 2 : // South
    // width of corridor
    for( unsigned int ind_c = 0; ind_c < src_cells.size(); ++ind_c ) {
      // length of path
      for( unsigned int ind_p = 0; ind_p < length; ++ind_p ) {
	cell = CellPtr( new Cell( src_cells[ind_c]->_y - ind_p - 1.0,
				  src_cells[ind_c]->_x,
				  src_cells[ind_c]->_z + (0.5+ind_p) * height / (dist-1),
				  -ang, 0.0 ));
	// link along path
	if( ind_p == 0 ) { // link to src if start
	  src_cells[ind_c]->_neighbors[2] = cell;
	  cell->_neighbors[0] = src_cells[ind_c];
	}
	else if( ind_p == length-1 ) { // link to des and previous
	  des_cells[ind_c]->_neighbors[0] = cell;
	  cell->_neighbors[2] = des_cells[ind_c];
	  cell->_neighbors[0] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[2] = cell;
	}
	else { // link to previous
	  cell->_neighbors[0] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[2] = cell;
	}
	// link to preceding "row" in path
	if( ind_c > 0 ) {
	  cell->_neighbors[3] = path[(ind_c-1)*length+ind_p];
	  path[(ind_c-1)*length+ind_p]->_neighbors[1] = cell;
	}
	path.push_back( cell );
      }
    }
    break;
  case 3 : // West
    // width of corridor
    for( unsigned int ind_c = 0; ind_c < src_cells.size(); ++ind_c ) {
      // length of path
      for( unsigned int ind_p = 0; ind_p < length; ++ind_p ) {
	cell = CellPtr( new Cell( src_cells[ind_c]->_x - ind_p - 1.0,
				  src_cells[ind_c]->_y,
				  src_cells[ind_c]->_z + (0.5+ind_p) * height / (dist-1),
				  0.0, -ang ));
	// link along path
	if( ind_p == 0 ) { // link to src if start
	  src_cells[ind_c]->_neighbors[3] = cell;
	  cell->_neighbors[1] = src_cells[ind_c];
	}
	else if( ind_p == length-1 ) { // link to des and previous
	  des_cells[ind_c]->_neighbors[1] = cell;
	  cell->_neighbors[3] = des_cells[ind_c];
	  cell->_neighbors[1] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[3] = cell;
	}
	else { // link to previous
	  cell->_neighbors[1] = path[path.size()-1];
	  path[path.size()-1]->_neighbors[3] = cell;
	}
	// link to preceding "row" in path
	if( ind_c > 0 ) {
	  cell->_neighbors[0] = path[(ind_c-1)*length+ind_p];
	  path[(ind_c-1)*length+ind_p]->_neighbors[2] = cell;
	}
	path.push_back( cell );
      }
    }
    break;
  }
  // add to ground
  for( unsigned int ind_p = 0; ind_p < path.size(); ++ind_p ) {
    _ground->_cells.push_back( path[ind_p] );
  }

  notify_observers();
}
// *****************************************************************************
/**
 * Return the cell under the player or null if above void.
 */
CellPtr World::get_cell_at( float x, float y, float z , bool verb)
{
  float dist_min = DBL_MAX;
  CellPtr res_cell = CellPtr();
  for( unsigned int ind_c = 0; ind_c < _ground->_cells.size(); ++ind_c ) {
    CellPtr cell = _ground->_cells[ind_c];
    // Project to a cell ?
    if( fabsf(x - cell->_x) < Cell::size and fabsf(y - cell->_y) < Cell::size ) {
      // Compute its "projection"
      float cell_z = cell->get_z_at( x, y );
      // "above" and closest to the cell
      if( (z - cell_z) >= 0.0 and (z - cell_z) < dist_min ) {
      res_cell = cell;
      dist_min = z - cell_z;
      }
    }
  }
  if( verb ) {
    if( res_cell ) {
      std::cout << "[World::get_cell_at] on " << res_cell->repr_dump() << " ZZ=" << dist_min << "\n";
    }
    else {
      std::cout << "[World::get_cell_at] void\n";
    }
  }
  return res_cell;
}
// *****************************************************************************

