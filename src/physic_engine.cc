/* -*- coding: utf-8 -*- */

#include "physic_engine.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
PhysicEngine::PhysicEngine( GameModelPtr model )
{
  _model = model;
}
/** Destruction */
PhysicEngine::~PhysicEngine()
{
}
//*********************************************************************** STRING
std::string PhysicEngine::dump_string()
{
  std::stringstream ss;
  
  ss << "PhysicEngine::dump_string()" << "\n";
  
  return ss.str();
}
//******************************************************************************
//******************************************************************************
void PhysicEngine::update( double time_current )
{
  // Delta time
  double dt = time_current - _time;
  
  // For every Player
  {
    PlayerPtr pl = _model->_player;
  }
  
}
