// -*- coding: utf-8 -*-

#include "game_observer.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
GameObserver::GameObserver( GameModelPtr model )
{
  _game = model;
}
/** Destruction */
GameObserver::~GameObserver()
{
}
//*********************************************************************** STRING
std::string GameObserver::dump_string()
{
  std::stringstream ss;
  
  ss << "GameObserver::dump_string()" << "\n";
  
  return ss.str();
}
//************************************************************************* INIT
void GameObserver::init( ScenePtr scene ) 
{
  // Graphic elmement
  _world_scigl = WorldSCIGLPtr( new WorldSCIGL( _game->_world ));
  _game->_world->attach_observer( _world_scigl );

  // Add to scene
  scene->add( _world_scigl );
}
//******************************************************************************
