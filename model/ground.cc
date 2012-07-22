// -*- coding: utf-8 -*-

#include <sstream>
#include <iostream>
#include "ground.h"

// *****************************************************************************
Ground::Ground(void) {}
Ground::Ground( Ground& other_g ) 
{
  std::cerr << "@@@ Ground::Ground( Ground& other_g ) \n";
}
Ground::~Ground(void)
{
}
// *****************************************************************************
std::string Ground::repr_dump()
{
  std::stringstream ss;
  if( _cells.size() == 0 ) {
    return "-empty-";
  }
  
  for( unsigned int ind_c = 0; ind_c < _cells.size(); ++ind_c ) {
    ss << _cells[ind_c]->repr_dump() << "\n";
  }
  return ss.str();
}
// *****************************************************************************
