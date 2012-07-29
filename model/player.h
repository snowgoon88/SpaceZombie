/* -*- coding: utf-8 -*- */

#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "utils.h"
#include "model.h"
#include "point.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class Player> PlayerPtr;

/**
 * Player has a phystate and an angle of rotation around Oz.
 * Its interna state also has a position and a speed.
 */
class Player : public Model
{
public:
  /** Creation */
  Player();
  Player( TVec3 pos, float ang_Oz_rad, float forward_speed=0.0f);
  /** Destruction */
  virtual ~Player();
  
  /** display string */
  std::string dump_str();

  /** set position */
  void set_position( TVec3 pos );
  /** set direction */
  void set_dir( float ang_Oz_rad );
  /** set_speed */
  void set_speed( float ang_Oz_rad, float norm );
  void set_speed( TVec3 speed );
  
public: // Intern
  /** Align to speed vector : update _ang_0z */
  void align_to_speed();
  
public: // Variables
  /** physical state*/
  PhyPointPtr _phystate;
  /** Dir */
  float _ang_Oz;
};
#endif // __PLAYER_H_
