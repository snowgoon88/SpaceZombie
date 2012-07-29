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
  
  _player_scigl = PlayerSciglPtr( new PlayerScigl( _game->_player ));
  _game->_player->attach_observer( _player_scigl );

  _player_tag = TagSciglPtr( new TagScigl( std::string("Player"), &(_game->_player->_pos), 1.0f ));

  // Add to scene
  scene->add( _world_scigl );
  scene->add( _player_scigl );
  scene->add( _player_tag );
}
//******************************************************************************
