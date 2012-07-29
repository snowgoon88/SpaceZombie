// -*- coding: utf-8 -*-

#include "player.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
Player::Player() : Model()
{
  _phystate = PhyPointPtr( new PhyPoint() );
  align_to_speed();
}
/** Creation with pose */
Player::Player( TVec3 pos, float ang_Oz_rad, float forward_speed) : Model()
{
  _phystate = PhyPointPtr( new PhyPoint( pos ));
  set_speed( ang_Oz_rad, forward_speed );
}
/** Destruction */
Player::~Player()
{
}
//*********************************************************************** STRING
std::string Player::dump_str()
{
  std::stringstream ss;
  
  ss << "Player: " << _phystate->dump_str() << " ang=" << SETPREC(1) << to_deg(_ang_Oz) << "\n";
  
  return ss.str();
}
//************************************************************************** SET
void Player::set_position( TVec3 pos ) 
{
  _phystate->_pos = pos;
  notify_observers();
}
void Player::set_dir( float ang_Oz_rad ) 
{
  _ang_Oz = ang_Oz_rad;
  notify_observers();
}
void Player::set_speed( float ang_Oz_rad, float norm )
{
  if( fabs(norm) > 0.00001 ) {
    _phystate->_speed = TVec3( norm*cosf(ang_Oz_rad),
			       norm*sinf(ang_Oz_rad),
			       0.0f);
    align_to_speed();
  }
  else {
    _phystate->_speed = TVec3(0.0f, 0.0f, 0.0f);
    set_dir( ang_Oz_rad );
  }
  notify_observers();

}
void Player::set_speed( TVec3 speed )
{
  _phystate->_speed = speed;
  align_to_speed();
  notify_observers();
}
//************************************************************************* ALIGN
void Player::align_to_speed()
{
  float dummy;
  ang_from_vec( _phystate->_speed, _ang_Oz, dummy);
}
//******************************************************************************
