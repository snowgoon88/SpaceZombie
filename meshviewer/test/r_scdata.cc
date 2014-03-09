/* -*- coding: utf-8 -*- */

#include "file_scdata.h"
#include "color.h"

//******************************************************************************
int main( int argc, char *argv[] )
{
  FileSCData fscdata( "SCData/data/misc/cube1m.mdl-msh000" );
  std::cout << fscdata.str_brief() << "\n";
  fscdata.read( true );

  std::cout << "fscdata.dump() ********************" << "\n";
  fscdata.dump( std::cout );

  std::cout << "fscdata.str_triangle() ************" << "\n";
  std::cout << fscdata.str_triangle( 0 ) << "\n";
  std::cout << fscdata.str_triangle( 3 ) << "\n";
  std::cout << fscdata.str_triangle( 6 ) << "\n";

  Color<char> col_c( (char *) &(fscdata._raw_vertex[0][12]) );
  //Color<char> col_c;
  std::cout << "COL_C=" << col_c.str_dump() << "\n";
  
  return 0;
}
