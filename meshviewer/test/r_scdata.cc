/* -*- coding: utf-8 -*- */

#include "file_scdata.h"

//******************************************************************************
int main( int argc, char *argv[] )
{
  FileSCData fscdata( "SCData/data/misc/cube1m.mdl-msh000" );
  std::cout << fscdata.dump_string() << "\n";
  fscdata.read( true );

  return 0;
}
