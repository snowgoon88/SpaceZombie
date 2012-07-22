/* -*- coding: utf-8 -*- */

#ifndef __GAME_MODEL_H_
#define __GAME_MODEL_H_

#include <string>

#include "world.h"
#include "player.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class GameModel> GameModelPtr;

/**
 * The GameModel is made of a World.
 */
class GameModel
{
public:
  /** Creation */
  GameModel();
  /** Destruction */
  virtual ~GameModel();
  
  /** display string */
  std::string dump_string();

  /** Init */
  virtual void init();

public: // Variables
  /** The Environment */
  WorldPtr _world;
  /** The player */
  PlayerPtr _player;
};
#endif // __GAME_MODEL_H_
