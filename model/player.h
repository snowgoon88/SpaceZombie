/* -*- coding: utf-8 -*- */

#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "utils.h"
#include "model.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class Player> PlayerPtr;

/**
 * Player has a position and an angle of rotation around Oz.
 */
class Player : public Model
{
public:
  /** Creation */
  Player();
  Player( TVec3 pos, float ang_Oz_rad );
  /** Destruction */
  virtual ~Player();
  
  /** display string */
  std::string dump_string();

  /** set position */
  void set_position( TVec3 pos );
  /** set direction */
  void set_dir( float ang_Oz_rad );
  
public: // Variables
  /** position */
  TVec3 _pos;
  /** Dir */
  float _ang_Oz;
};
#endif // __PLAYER_H_
