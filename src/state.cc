// -*- coding: utf-8 -*-

#include "state.h"

// *****************************************************************************
State::State( unsigned int id, std::string name )
{
  _id = id;
  _name = name;
}
State::State( State& other_s )
{
  _id = other_s._id;
  _name = other_s._name;
}
State::~State( void )
{
}
// *****************************************************************************
bool State::operator ==( const State& s) const
{
  if( s._id != _id ) {
    return false;
  }
  if( s._name.compare( _name ) != 0 ) {
    return false;
  }
  return true;
}
// *****************************************************************************
