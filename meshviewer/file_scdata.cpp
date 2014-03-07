// -*- coding: utf-8 -*-

#include "file_scdata.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
FileSCData::FileSCData(std::string filename)
{
  _filename = filename;

  _size_vertex = 0:
  _nb_vertex = 0;

}
/** Destruction */
FileSCData::~FileSCData()
{
}
//*********************************************************************** STRING
std::string FileSCData::dump_string()
{
  std::stringstream ss;
  
  ss << "FileSCData::dump_string()" << "\n";
  
  return ss.str();
}
//******************************************************************************
void FileSCData::read( bool fg_verb=FALSE )
{
  // try to open file
  FILE *fp = NULL;
  fp = fopen( _filename.c_str(), "r");
  if (fp == NULL) {
    std::cerr << "Error opening : " << filename << "\n";
    return;
  }
  
  // read header
  // Unknown 0x00 -> 0x07
  for( int i = 0; i < 0x08; ++i) {
    read_uchar( file );
  }
  // 0x08 : size vertex, 0x0C : nb vertex 
  _size_vertex = read_uint( file );
  _nb_vertex = read_uint( file );
  if (fg_verb) {
    printf( "%02Xh : %02Xh => %d (size_vertex)\n", 0x08, size_vertex, size_vertex );
    printf( "%02Xh : %02Xh => %d (nb_vertex)\n", 0x0C, nb_vertex, nb_vertex );
  }
  // Unknown -> 0x44
  for( int i = 0x10; i < 0x44; ++i) {
    read_uchar( file );
  }
  
  // read_vertex
  for( unsigned int i = 0; i < nb_vertex; ++i ) {
    unsigned char vertex = new (unsigned char)[_size_vertex];
    fread( (void*) (&vertex), sizeof(unsigned char), _size_vertex, fp);
    _raw_vertex.push_back( &vertex );
    // read xyz from vertex
    float x,y,z;
    memcpy( &x, &(vertex[0]), sizeof(float));
    memcpy( &x, &(vertex[4]), sizeof(float));
    memcpy( &x, &(vertex[8]), sizeof(float));
    _v_xyz.push_back( TVec3(x,y,z) );
    // read rgba from vertex
    unsigned char r,g,b,a;
    TColorUC col_uc;
    col_uc.r = vertex[12];
    col_uc.g = vertex[13];
    col_uc.b = vertex[14];
    col_uc.a = vertex[15];
    _v_rgba.push_back( col_uc );
  }
  
  // read indices to the end
  while( feof( fp ) == false ) {
    unsigned short pt0 = read_ushort( file );
    unsigned short pt1 = read_ushort( file );
    unsigned short pt2 = read_ushort( file );
    _v_indices.push_back( pt0 );
    _v_indices.push_back( pt1 );
    _v_indices.push_back( pt2 );
  }
  
  close( fp );
  
  if (fg_verb) {
    printf( "Read %d vertex (out of %d), %d indices, for %d triangles\n",
	    _raw_vertex.size(), _nb_vertex, _v_indices.size(), _v_indices.size()/3 );
  }
}

