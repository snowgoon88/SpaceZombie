// -*- coding: utf-8 -*-

#include "player.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
Player::Player() : Model()
{
  _pos = TVec3( 0, 0, 0);
  _ang_Oz = 0.0;
}
/** Creation with pose */
Player::Player( TVec3 pos, float ang_Oz_rad ) : Model()
{
  _pos = pos;
  _ang_Oz = ang_Oz_rad;
}
/** Destruction */
Player::~Player()
{
}
//*********************************************************************** STRING
std::string Player::dump_string()
{
  std::stringstream ss;
  
  ss << "Player::dump_string()" << "\n";
  
  return ss.str();
}
//*********************************************************************** UPDATE
void Player::set_position( TVec3 pos ) 
{
  _pos = pos;
  notify_observers();
}
void Player::set_dir( float ang_Oz_rad ) 
{
  _ang_Oz = ang_Oz_rad;
  notify_observers();
}
//******************************************************************************
