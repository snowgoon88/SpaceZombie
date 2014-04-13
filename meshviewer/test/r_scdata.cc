/* -*- coding: utf-8 -*- */

#include "file_scdata.h"     // SC data files
#include "color.h"           // IColor abstrat of TColor<T>
#include "mesh_model.h"      // Mesh as triangles

//******************************************************************************
int main( int argc, char *argv[] )
{
  // FileSCData fscdata( "SCData/data/misc/cube1m.mdl-msh000" );
  FileSCData fscdata( "SCData/data/race1_l_t1.mdl-msh000" );
  std::cout << fscdata.str_brief() << "\n";
  fscdata.read( true );

  std::cout << "fscdata.dump() ********************" << "\n";
  fscdata.dump( std::cout );

  std::cout << "fscdata.str_triangle() ************" << "\n";
  std::cout << fscdata.str_triangle( 0 ) << "\n";
  std::cout << fscdata.str_triangle( 3 ) << "\n";
  std::cout << fscdata.str_triangle( 6 ) << "\n";

  TColor<char> col_c( (char *) &(fscdata._raw_vertex[0][12]) );
  //TColor<char> col_c;
  std::cout << "COL_C=" << col_c.str_dump() << "\n";


  fscdata.read_v_color<unsigned char>( (unsigned int) 0x0C );
  for( unsigned int i=0; i<fscdata._v_color.size(); ++i ) {
    std::cout << i << " " << fscdata._v_color[i]->str_dump() << "\n";
  }

  // Create Mesh
  MeshModel mesh;
  std::cout << "****CREATION" << "\n";
  mesh.dump( std::cout );
  std::cout << "****COPY from SCData" << "\n";
  mesh.attach( &fscdata );
  mesh.dump( std::cout );
  return 0;
}
