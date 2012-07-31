/* -*- coding: utf-8 -*- */

#include "physic_engine.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
PhysicEngine::PhysicEngine( GameModelPtr model )
{
  _model = model;
}
/** Destruction */
PhysicEngine::~PhysicEngine()
{
}
//*********************************************************************** STRING
std::string PhysicEngine::dump_string()
{
  std::stringstream ss;
  
  ss << "PhysicEngine::dump_string()" << "\n";
  
  return ss.str();
}
//*********************************************************************** Update
void PhysicEngine::update( double delta_time_ms )
{
  // Delta time
  double dt = delta_time_ms;
  
  // For every Player
  {
    // Look for the cell it will be after dt.
    PhyPointPtr pt = _model->_player->_phystate;
    TVec3 next_pt = pt->get_future_pos( dt );

    unsigned int dir;
    if( pt->_curr_cell->is_leaving_cell( next_pt, dir )) {
      // Check if neigbor cell in the dir of mouvement
      CellPtr neighbor_cell = pt->_curr_cell->_neighbors[dir];
      if( neighbor_cell ) {
	// update player position which stick at cell
	next_pt(2) = neighbor_cell->get_z_at( next_pt(0), next_pt(1) );
	pt->_pos = next_pt;
	pt->_curr_cell = neighbor_cell;
      }
      else {
	// update player_position to cell border
	next_pt = pt->_curr_cell->clamp_to_cell( pt->_pos, next_pt, dir);
	next_pt(2) = pt->_curr_cell->get_z_at( next_pt(0), next_pt(1) );
	pt->_pos = next_pt;
      }
    }
    else {
      // stick to current cell
      next_pt(2) = pt->_curr_cell->get_z_at( next_pt(0), next_pt(1) );
      pt->_pos = next_pt;
    }
  }
  
  // set to new time.
  _time += dt;
}
//************************************************************************ Start
void PhysicEngine::start( double time_current )
{
  _time = 0;
}
//******************************************************************************
