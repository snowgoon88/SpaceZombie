/* -*- coding: utf-8 -*- */

#ifndef __GAME_OBSERVER_H_
#define __GAME_OBSERVER_H_

#include "game_model.h"

#include "scene.h"
#include "world_scigl.h"
#include "player_scigl.h"
#include "tag_scigl.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class GameObserver> GameObserverPtr;

/**
 * Create and manage Observers of the Game :
 * - World as SCIGL.
 */
class GameObserver
{
public:
  /** Creation */
  GameObserver( GameModelPtr model );
  /** Destruction */
  virtual ~GameObserver();
  
  /** display string */
  std::string dump_string();

  /** Init of Scigl and text observer */
  virtual void init( ScenePtr scene );

public: // Variables
  /** Model of World */
  GameModelPtr _game;
  /** World, graphic */
  WorldSCIGLPtr _world_scigl;
  /** Player graphic */
  PlayerSciglPtr _player_scigl;
  /** Tag for player */
  TagSciglPtr _player_tag;
};
#endif // __GAME_OBSERVER_H_
