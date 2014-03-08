/* -*- coding: utf-8 -*- */

#include "file_scdata.h"

//******************************************************************************
int main( int argc, char *argv[] )
{
  FileSCData fscdata( "SCData/data/misc/cube1m.mdl-msh000" );
  std::cout << fscdata.str_brief() << "\n";
  fscdata.read( true );

  std::cout << "fscdata.dump() ********************" << "\n";
  fscdata.dump( std::cout );
  return 0;
}
