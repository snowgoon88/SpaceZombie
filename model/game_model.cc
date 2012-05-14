// -*- coding: utf-8 -*-

#include "game_model.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
GameModel::GameModel()
{
  init();
}
/** Destruction */
GameModel::~GameModel()
{
}
//*********************************************************************** STRING
std::string GameModel::dump_string()
{
  std::stringstream ss;
  
  ss << "GameModel::dump_string()" << "\n";
  
  return ss.str();
}
//************************************************************************* INIT
void GameModel::init() 
{
  // Create a world
  _world = WorldPtr( new World );
  // Rooms
  _world->add_new_room( 0.0, 0.0, 0.0, 1, 4);
  _world->add_new_room( 2.0, 0.0, 0.0, 1, 2);
  _world->add_new_room( 3.0, 2.0, 1.0, 1, 2);
  // Connexions
  std::vector< CellPtr > start, end;
  start.push_back( _world->_ground->_cells[0] );
  end.push_back( _world->_ground->_cells[4] );
  _world->connect_cells( start, end ); // 1 to 1 connection  
  start.clear();
  start.push_back( _world->_ground->_cells[2] );
  start.push_back( _world->_ground->_cells[3] );
  end.clear();
  end.push_back( _world->_ground->_cells[6] );
  end.push_back( _world->_ground->_cells[7] );
  _world->connect_cells( start, end ); // 2 to 2 connection

  // No player ??
  // _world->_player->_x = 3.0;
  // _world->_player->_y = 2.0;
  // _world->_player->_z = 2.0;
  // _world->_player->_vx = ( -0.2 );
  // _world->_player->_vy = (  0.0 ); 

}
//******************************************************************************
