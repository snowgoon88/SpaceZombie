// -*- coding: utf-8 -*-
/**
 * Teste quelques fonctionnalites du World
 */

#include "world.h"
#include <iostream>

void test_create_world()
{
  WorldPtr w = WorldPtr( new World );
  std::cout << "*** Genèse ***\n" << w->repr_dump() << "\n";

  w->add_new_cell( -1.0, -1.0, 0.0 );
  std::cout << "*** Add ***\n" << w->repr_dump() << "\n";

  w->add_new_room( 2.0, 0.0, 0.0, 3, 4);
  std::cout << "*** Room ***\n" << w->repr_dump() << "\n";
}
// -----------------------------------------------------------------------------
void test_corridor()
{
  WorldPtr w = WorldPtr( new World );
  w->add_new_room( 0.0, 0.0, 0.0, 1, 4);
  w->add_new_room( 2.0, 0.0, 0.0, 1, 2);
  w->add_new_room( 3.0, 2.0, 1.0, 1, 2);
  std::cout << "*** Genèse ***\n" << w->repr_dump() << "\n";

  std::vector< CellPtr > start;
  std::vector< CellPtr > end;

  start.push_back( w->_ground->_cells[0] );
  std::cout << "start < end : different size\n";
  w->connect_cells( start, end );  
  end.push_back( w->_ground->_cells[0] );
  std::cout << "start = end : no direction\n";
  w->connect_cells( start, end );

  end.clear();
  end.push_back( w->_ground->_cells[1] );
  std::cout << "start sides end : no length\n";
  w->connect_cells( start, end );    

  end.clear();
  end.push_back( w->_ground->_cells[5] );
  std::cout << "start to end, should not work (direction)\n";
  w->connect_cells( start, end );  

  end.clear();
  end.push_back( w->_ground->_cells[4] );
  std::cout << "start to end, should work\n";
  w->connect_cells( start, end );  
  std::cout << "*** First ***\n" << w->repr_dump() << "\n";

  start.clear();
  start.push_back( w->_ground->_cells[1] );
  start.push_back( w->_ground->_cells[2] );
  end.clear();
  end.push_back( w->_ground->_cells[5] );
  end.push_back( w->_ground->_cells[6] );
  std::cout << "start to end : different heights\n";
  w->connect_cells( start, end );  

  start.clear();
  start.push_back( w->_ground->_cells[2] );
  start.push_back( w->_ground->_cells[3] );
  end.clear();
  end.push_back( w->_ground->_cells[6] );
  end.push_back( w->_ground->_cells[5] );
  std::cout << "start to end : different dirs\n";
  w->connect_cells( start, end );  

  end.clear();
  end.push_back( w->_ground->_cells[6] );
  end.push_back( w->_ground->_cells[7] );
  std::cout << "start to end : width2\n";
  w->connect_cells( start, end );  
  std::cout << "*** second ***\n" << w->repr_dump() << "\n";

  
}
// *****************************************************************************
int main( int argc, char *argv[] )
{
  //std::string filename( argv[1] );
  
  //test_create_world();
  test_corridor();
}
