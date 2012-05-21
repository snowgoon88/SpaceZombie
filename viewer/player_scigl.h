/* -*- coding: utf-8 -*- */

#ifndef __PLAYER_SCIGL_H_
#define __PLAYER_SCIGL_H_

#include <string>
#include "observer.h" 
#include "object.h"
#include "utils.h"
#include "player.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class PlayerScigl> PlayerSciglPtr;


/**
 * A player is displayed as a kind of 3DArrowHead
 */
class PlayerScigl : public Observer, public Object
{
public:
  /** Creation */
  PlayerScigl( PlayerPtr model );
  /** Destruction */
  virtual ~PlayerScigl();
  
  /** display string */
  std::string dump_string();

public: // Observer
  virtual void update( int signal=0 );
public: // Object
  virtual void render();

public: // Variables
  PlayerPtr _model;
};


#endif // __PLAYER_SCIGL_H_
