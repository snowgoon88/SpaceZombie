// -*- coding: utf-8 -*-

// try to read second, and to list the first few triangles

#include <stdio.h>
#include "utils.h"

//******************************************************************************
std::vector<TVec3> _v_vertex;
std::vector<unsigned int> _v_indices;
std::vector<unsigned char *> _v_ukn0, _v_ukn1;
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
void tchar_to_uchar( char *out, unsigned char *tc, unsigned int length ) 
{
  // clear out
  strcpy( out, "");

  char buffer[100];
  for( unsigned int i=0; i<length; ++i) {
    sprintf( buffer, "%02X ", tc[i] );
    strcat( out, buffer );
  }
}
void tchar_to_short( char *out, unsigned char *tc, unsigned int length ) 
{
  // clear out
  strcpy( out, "");

  char buffer[100];
  unsigned short val;
  for( unsigned int i=0; i<length; i += sizeof(unsigned short)) {
    memcpy( &val, &(tc[i]), sizeof(short));
    sprintf( buffer, "%6d ", val );
    strcat( out, buffer );
  }
}
void tchar_to_int( char *out, unsigned char *tc, unsigned int length ) 
{
  // clear out
  strcpy( out, "");

  char buffer[100];
  int val;
  for( unsigned int i=0; i<length; i += sizeof(int)) {
    memcpy( &val, &(tc[i]), sizeof(int));
    sprintf( buffer, "%10d ", val );
    strcat( out, buffer );
  }
}
//*******************************************************************************
void read_mesh_18h( FILE *file ) 
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
//*******************************************************************************
void read_mesh_20h( FILE *file ) 
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
  // Read Vertex
  for( unsigned int i = 0; i < nb_vertex; ++i) {
    // x,y,z coordinate as float
    float x = read_float( file );
    float y = read_float( file );
    float z = read_float( file );
    _v_vertex.push_back( TVec3(x,y,z) );
    //printf( "%02Xh : xyz = %2.3f; %2.3f; %2.3f\n", 0x44+i*size_vertex, x,y,z);
    // 8 unknown char
    unsigned char * ukn0 = new unsigned char[8];
    for( unsigned int j=0; j<8; ++j) {
      ukn0[j] = read_uchar( file );
    }
    _v_ukn0.push_back( ukn0 );
    // u, v coordinate
    float u = read_float( file );
    float v = read_float( file );
    //printf( "     : xv = %2.3f; %2.3f\n", u, v);
    // 4 unknown char
    unsigned char * ukn1 = new unsigned char[4];
    for( unsigned int j=0; j<4; ++j) {
      ukn1[j] = read_uchar( file );
    }
    _v_ukn1.push_back( ukn1 );
  }
  // read triangles to the end
  unsigned int adr_file = 0x44 + nb_vertex * size_vertex;
  while( feof( file ) == false ) {
    unsigned short pt0 = read_ushort( file );
    unsigned short pt1 = read_ushort( file );
    unsigned short pt2 = read_ushort( file );
    _v_indices.push_back( pt0 );
    _v_indices.push_back( pt1 );
    _v_indices.push_back( pt2 );
    //printf ( "%2Xh : %2d - %2d - %2d\n", adr_file, pt0, pt1, pt2 ); 
    adr_file += 3 * sizeof(unsigned short);
  }
  
  // Write 1st triangle
  char out0[100], out1[100];
  unsigned int nb_shown = 18;
  for( unsigned int i=0; i<nb_shown; ++i) {
    if (i%3 == 0) {
      printf( "**********\n");
    }
    unsigned int idx = _v_indices[i];
    TVec3 ver = _v_vertex[idx];
    printf( "%2d : xyz = %2.3f; %2.3f; %2.3f\n", idx, ver(0), ver(1), ver(2));
    tchar_to_uchar( out0, _v_ukn0[idx], 8);
    tchar_to_uchar( out1, _v_ukn1[idx], 4);
    printf( "     %s - %s\n", out0, out1);
  }
  printf( "\n\n\n" );
  for( unsigned int i=0; i<nb_shown; ++i) {
    if (i%3 == 0) {
      printf( "**********\n");
    }
    unsigned int idx = _v_indices[i];
    TVec3 ver = _v_vertex[idx];
    printf( "%2d : xyz = %2.3f; %2.3f; %2.3f\n", idx, ver(0), ver(1), ver(2));
    tchar_to_short( out0, _v_ukn0[idx], 8);
    tchar_to_short( out1, _v_ukn1[idx], 4);
    printf( "     %s - %s\n", out0, out1);
  }

  printf( "\n\n\n" );
  for( unsigned int i=0; i<nb_shown; ++i) {
    if (i%3 == 0) {
      printf( "**********\n");
    }
    unsigned int idx = _v_indices[i];
    TVec3 ver = _v_vertex[idx];
    printf( "%2d : xyz = %2.3f; %2.3f; %2.3f\n", idx, ver(0), ver(1), ver(2));
    tchar_to_int( out0, _v_ukn0[idx], 8);
    tchar_to_int( out1, _v_ukn1[idx], 4);
    printf( "     %s - %s\n", out0, out1);
  }
}

//******************************************************************************
int main( int argc, char *argv[] )
{
  //FILE *fp = fopen( "data/misc/cube1m.mdl-msh000", "r");
  FILE *fp = fopen( "data/ship_race2_s_t4/race2_s_t4.mdl-msh000", "r");

  // // Read first ten uchar
  // for( int i = 0; i < 0x0C; ++i) {
  //   unsigned char var = read_uchar( fp );
  //   printf( "%02Xh : %02Xh = %3d\n", i, var, var); 
  // }
  read_mesh_20h( fp );

  return 0;
}

