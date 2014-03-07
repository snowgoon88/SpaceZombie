// -*- coding: utf-8 -*-

#include "file_scdata.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

//********************************************************************* CREATION
/** Creation */
FileSCData::FileSCData(std::string filename)
{
  _filename = filename;

  _size_vertex = 0;
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
  
  ss << "FileSCData: " << _filename  << "\n";
  ss << "  read " << _raw_vertex.size() << " vertex out of " << _nb_vertex;
  ss << ", " << _v_indices.size() << " indices => " << _v_indices.size()/3 << " triangles";
  ss << "\n";

  return ss.str();
}
//******************************************************************************
void FileSCData::read( bool fg_verb )
{
  // try to open file
  FILE *fp = NULL;
  fp = fopen( _filename.c_str(), "r");
  if (fp == NULL) {
    std::cerr << "Error opening : " << _filename << "\n";
    return;
  }
  
  // read header
  // Unknown 0x00 -> 0x07
  for( int i = 0; i < 0x08; ++i) {
    unsigned char uc;
    fread( (void*) (&uc), sizeof(uc), 1, fp);
  }
  // 0x08 : size vertex, 0x0C : nb vertex 
  fread( (void*) (&_size_vertex), sizeof(_size_vertex), 1, fp);
  fread( (void*) (&_nb_vertex), sizeof(_nb_vertex), 1, fp);
  if (fg_verb) {
    printf( "%02Xh : %02Xh => %d (size_vertex)\n", 0x08, _size_vertex, _size_vertex );
    printf( "%02Xh : %02Xh => %d (nb_vertex)\n", 0x0C, _nb_vertex, _nb_vertex );
  }
  // Unknown -> 0x44
  for( int i = 0x10; i < 0x44; ++i) {
    unsigned char uc;
    fread( (void*) (&uc), sizeof(uc), 1, fp);
  }
  
  // read_vertex
  for( unsigned int i = 0; i < _nb_vertex; ++i ) {
    unsigned char *vertex = new unsigned char[_size_vertex];
    fread( (void*) (vertex), sizeof(unsigned char), _size_vertex, fp);
    _raw_vertex.push_back( vertex );
    // read xyz from vertex
    float x,y,z;
    memcpy( &x, &(vertex[0]), sizeof(float));
    memcpy( &x, &(vertex[4]), sizeof(float));
    memcpy( &x, &(vertex[8]), sizeof(float));
    _v_xyz.push_back( TVec3(x,y,z) );
    // read rgba from vertex
    TColorUC col_uc;
    col_uc.r = vertex[12];
    col_uc.g = vertex[13];
    col_uc.b = vertex[14];
    col_uc.a = vertex[15];
    _v_rgba.push_back( col_uc );
  }
  
  // read indices to the end
  while( feof( fp ) == false ) {
    unsigned short pt0, pt1, pt2;
    fread( (void*) (&pt0), sizeof(pt0), 1, fp);
    fread( (void*) (&pt1), sizeof(pt2), 1, fp);
    fread( (void*) (&pt2), sizeof(pt2), 1, fp);
    _v_indices.push_back( pt0 );
    _v_indices.push_back( pt1 );
    _v_indices.push_back( pt2 );
  }
  
  fclose( fp );
  
  if (fg_verb) {
    std::cout << dump_string() << "\n";
  }
}

