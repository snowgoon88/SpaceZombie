/* -*- coding: utf-8 -*- */

#ifndef __PHYSIC_ENGINE_H__
#define __PHYSIC_ENGINE_H__

#include "utils.h"
#include "game_model.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class PhysicEngine> PhysicEnginePtr;

/**
 * Update 'Players' in the world, according to their position, speed
 * and the world.
 * 
 * Current implementation:
 * Rebound on cell edges (no neighbors). Update speed vector.
 */
class PhysicEngine
{
public:
  /** Creation */
  PhysicEngine( GameModelPtr model);
  /** Destruction */
  virtual ~PhysicEngine();
  
  /** display string */
  std::string dump_string();

  /** update according to time */
  virtual void update();

public: // Variables
  /** Every object of the game */
  GameModelPtr _model;
  /** Physic time */
  double _time;
};

#endif // __PHYSIC_ENGINE_H__
