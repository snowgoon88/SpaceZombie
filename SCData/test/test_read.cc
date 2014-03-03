// -*- coding: utf-8 -*-

#include <stdio.h>

//******************************************************************************
unsigned char read_uchar( FILE *file )
{
  unsigned char var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
unsigned int read_ushort( FILE *file )
{
  unsigned short var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
unsigned int read_uint( FILE *file )
{
  unsigned int var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
} 
float read_float( FILE *file )
{
  float var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
//*******************************************************************************
void read_mesh( FILE *file ) 
{
  // Unknown 0x00 -> 0x07
  for( int i = 0; i < 0x08; ++i) {
    read_uchar( file );
  }
  // 0x08 : size vertex, 0x0C : nb vertex 
  unsigned int size_vertex = read_uint( file );
  unsigned int nb_vertex = read_uint( file );
  printf( "%02Xh : %02Xh => %d (size_vertex)\n", 0x08, size_vertex, size_vertex );
  printf( "%02Xh : %02Xh => %d (nb_vertex)\n", 0x0C, nb_vertex, nb_vertex );
  // Unknown -> 0x44
  for( int i = 0x10; i < 0x44; ++i) {
    read_uchar( file );
  }
  // Read 3 floats
  for( unsigned int i = 0; i < nb_vertex; ++i) {
    // x,y,z coordinate as float
    float x = read_float( file );
    float y = read_float( file );
    float z = read_float( file );
    printf( "%02Xh : xyz = %2.3f; %2.3f; %2.3f\n", 0x44+i*size_vertex, x,y,z);
    // r,g,b,a as unsigned char
    unsigned char c_red = read_uchar( file );
    unsigned char c_blue = read_uchar( file );
    unsigned char c_green = read_uchar( file );
    unsigned char c_alpha = read_uchar( file );
    printf( "     : %3d %3d %3d %3d \n", c_red, c_blue, c_green, c_alpha);
    // u, v coordinate
    float u = read_float( file );
    float v = read_float( file );
    printf( "     : xv = %2.3f; %2.3f\n", u, v);
  }
  // read triangles to the end
  unsigned int adr_file = 0x44 + nb_vertex * size_vertex;
  while( feof( file ) == false ) {
    unsigned short pt0 = read_ushort( file );
    unsigned short pt1 = read_ushort( file );
    unsigned short pt2 = read_ushort( file );
    printf ( "%2Xh : %2d - %2d - %2d\n", adr_file, pt0, pt1, pt2 ); 
    adr_file += 3 * sizeof(unsigned short);
  }
}
//******************************************************************************
int main( int argc, char *argv[] )
{
  FILE *fp = fopen( "data/misc/cube1m.mdl-msh000", "r");

  // // Read first ten uchar
  // for( int i = 0; i < 0x0C; ++i) {
  //   unsigned char var = read_uchar( fp );
  //   printf( "%02Xh : %02Xh = %3d\n", i, var, var); 
  // }
  read_mesh( fp );

  return 0;
}

