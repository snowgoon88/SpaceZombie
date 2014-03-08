// -*- coding: utf-8 -*-

#include "file_scdata.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "math.h"

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
std::string FileSCData::str_brief()
{
  std::stringstream ss;
  
  ss << "FileSCData: " << _filename  << "\n";
  ss << "  read " << _raw_vertex.size() << " vertex out of " << _nb_vertex;
  ss << ", " << _v_indices.size() << " indices => " << _v_indices.size()/3 << " triangles";
  ss << "\n";

  return ss.str();
}
std::string FileSCData::str_triangle(unsigned int index)
{
  std::stringstream ss;
  
  ss << DFORMAT(4) << index << " : ";
  ss << DFORMAT(3) << _v_indices[index] << " -- ";
  ss << DFORMAT(3) << _v_indices[index+1] << " -- ";
  ss << DFORMAT(3) << _v_indices[index+2];
  ss << "\n";
  for( unsigned int i=0; i < 3; ++i) {
    unsigned short pt = _v_indices[index+i];
    ss << DFORMAT(4) << pt << " : ";
    ss << FFORMAT(6,3) << _v_xyz[pt](0) << ", ";
    ss << FFORMAT(6,3) << _v_xyz[pt](1) << ", ";
    ss << FFORMAT(6,3) << _v_xyz[pt](2);

    ss << " -- ";
    ss << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[pt].r) << ", ";
    ss << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[pt].g) << ", ";
    ss << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[pt].b) << ", ";
    ss << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[pt].a) << " :  ";
    float norm_uc = sqrtf( static_cast<unsigned>(_v_rgba_uc[pt].r) * static_cast<unsigned>(_v_rgba_uc[pt].r) + static_cast<unsigned>(_v_rgba_uc[pt].g) * static_cast<unsigned>(_v_rgba_uc[pt].g) + static_cast<unsigned>(_v_rgba_uc[pt].b) * static_cast<unsigned>(_v_rgba_uc[pt].b) ); 
    ss << FFORMAT(4,1) << norm_uc;

    ss << " -- ";
    ss << DFORMAT(4) << static_cast<int>(_v_rgba_c[pt].r) << ", ";
    ss << DFORMAT(4) << static_cast<int>(_v_rgba_c[pt].g) << ", ";
    ss << DFORMAT(4) << static_cast<int>(_v_rgba_c[pt].b) << ", ";
    ss << DFORMAT(4) << static_cast<int>(_v_rgba_c[pt].a) << " :  ";
    float norm_c = sqrtf( static_cast<int>(_v_rgba_c[pt].r) * static_cast<int>(_v_rgba_c[pt].r) + static_cast<int>(_v_rgba_c[pt].g) * static_cast<int>(_v_rgba_c[pt].g) + static_cast<int>(_v_rgba_c[pt].b) * static_cast<int>(_v_rgba_c[pt].b) ); 
    ss << FFORMAT(4,1) << norm_c;
    ss << "\n";
  }
  return ss.str();
}
/**
 * str_brief()
 * Vertex :   [i] : xyz -- rgba_uc : norm -- rgba_u : norm
 * Triangle : [i] : pt0, pt1, pt2
 */
void FileSCData::dump( std::ostream& out )
{
  
  out << str_brief();
  out << "Reading from _v_xyz[" << _v_xyz.size() << "]      ";
  out << " -- _v_rgba_uc[" << _v_rgba_uc.size() << "]             ";
  out << " -- _v_rgba_c[" << _v_rgba_c.size() << "]";
  out << "\n";
  for( unsigned int i=0; i<_v_xyz.size(); ++i ) {
    out << DFORMAT(4) << i << " : ";
    out << FFORMAT(6,3) << _v_xyz[i](0) << ", ";
    out << FFORMAT(6,3) << _v_xyz[i](1) << ", ";
    out << FFORMAT(6,3) << _v_xyz[i](2);

    out << " -- ";
    out << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[i].r) << ", ";
    out << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[i].g) << ", ";
    out << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[i].b) << ", ";
    out << DFORMAT(3) << static_cast<unsigned>(_v_rgba_uc[i].a) << " :  ";
    float norm_uc = sqrtf( static_cast<unsigned>(_v_rgba_uc[i].r) * static_cast<unsigned>(_v_rgba_uc[i].r) + static_cast<unsigned>(_v_rgba_uc[i].g) * static_cast<unsigned>(_v_rgba_uc[i].g) + static_cast<unsigned>(_v_rgba_uc[i].b) * static_cast<unsigned>(_v_rgba_uc[i].b) ); 
    out << FFORMAT(4,1) << norm_uc;

    out << " -- ";
    out << DFORMAT(4) << static_cast<int>(_v_rgba_c[i].r) << ", ";
    out << DFORMAT(4) << static_cast<int>(_v_rgba_c[i].g) << ", ";
    out << DFORMAT(4) << static_cast<int>(_v_rgba_c[i].b) << ", ";
    out << DFORMAT(4) << static_cast<int>(_v_rgba_c[i].a) << " :  ";
    float norm_c = sqrtf( static_cast<int>(_v_rgba_c[i].r) * static_cast<int>(_v_rgba_c[i].r) + static_cast<int>(_v_rgba_c[i].g) * static_cast<int>(_v_rgba_c[i].g) + static_cast<int>(_v_rgba_c[i].b) * static_cast<int>(_v_rgba_c[i].b) ); 
    out << FFORMAT(4,1) << norm_c;
    out << "\n";
  }
  out << "Reading from _v_indices[" << _v_indices.size() << "]\n";
  for( unsigned int i=0; i<_v_indices.size(); i = i+3 ) {
    out << DFORMAT(4) << i << " : ";
    out << DFORMAT(3) << _v_indices[i] << ", ";
    out << DFORMAT(3) << _v_indices[i+1] << ", ";
    out << DFORMAT(3) << _v_indices[i+2];
    out << "\n";
  }
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
    read_uchar( fp );
  }
  // 0x08 : size vertex, 0x0C : nb vertex
  _size_vertex = read_uint( fp );
  _nb_vertex = read_uint( fp );
  if (fg_verb) {
    printf( "%02Xh : %02Xh => %d (size_vertex)\n", 0x08, _size_vertex, _size_vertex );
    printf( "%02Xh : %02Xh => %d (nb_vertex)\n", 0x0C, _nb_vertex, _nb_vertex );
  }
  // Unknown -> 0x44
  for( int i = 0x10; i < 0x44; ++i) {
    read_uchar( fp );
  }
  
  // read_vertex
  for( unsigned int i = 0; i < _nb_vertex; ++i ) {
    unsigned char *vertex = new unsigned char[_size_vertex];
    fread( (void*) (vertex), sizeof(unsigned char), _size_vertex, fp);
    _raw_vertex.push_back( vertex );
    // read xyz from vertex
    float x,y,z;
    memcpy( &x, &(vertex[0]), sizeof(float));
    memcpy( &y, &(vertex[4]), sizeof(float));
    memcpy( &z, &(vertex[8]), sizeof(float));
    _v_xyz.push_back( TVec3(x,y,z) );
    // read rgba from vertex
    TColorUC col_uc;
    col_uc.r = vertex[12];
    col_uc.g = vertex[13];
    col_uc.b = vertex[14];
    col_uc.a = vertex[15];
    _v_rgba_uc.push_back( col_uc );
    TColorC col_c;
    col_c.r = vertex[12];
    col_c.g = vertex[13];
    col_c.b = vertex[14];
    col_c.a = vertex[15];
    _v_rgba_c.push_back( col_c );
    
  }
  
  // read indices to the end
  while( feof( fp ) == false ) {
    unsigned short pt0, pt1, pt2;
    pt0 = read_ushort( fp );
    pt1 = read_ushort( fp );
    pt2 = read_ushort( fp );
    _v_indices.push_back( pt0 );
    _v_indices.push_back( pt1 );
    _v_indices.push_back( pt2 );
  }
  
  fclose( fp );
  
  if (fg_verb) {
    std::cout << str_brief() << "\n";
  }
}
//*************************************************************** get_TColorUC
//******************************************************************************
void FileSCData::get_TColorUC( std::vector<TColorUC> * v_col,
			       unsigned int idx_start )
{
  unsigned int idx = idx_start;

  for (unsigned int i=0; i < _raw_vertex.size(); ++i) {
    TColorUC color;
    unsigned char * vertex = _raw_vertex[i];
    memcpy( &(color.r), &(vertex[idx]), sizeof(unsigned char));
    idx_start += sizeof(unsigned char);
    memcpy( &(color.g), &(vertex[idx]), sizeof(unsigned char));
    idx_start += sizeof(unsigned char);
    memcpy( &(color.b), &(vertex[idx]), sizeof(unsigned char));
    idx_start += sizeof(unsigned char);
    memcpy( &(color.a), &(vertex[idx]), sizeof(unsigned char));
    idx_start += sizeof(unsigned char);
    memcpy( &(color.g), &(vertex[idx]), sizeof(unsigned char));
    idx_start += sizeof(unsigned char);

    v_col->push_back( color );
  }

}
//*************************************************************************** 
//******************************************************************************
unsigned char FileSCData::read_uchar( FILE *file )
{
  unsigned char var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
unsigned int FileSCData::read_ushort( FILE *file )
{
  unsigned short var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
unsigned int FileSCData::read_uint( FILE *file )
{
  unsigned int var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
} 
float FileSCData::read_float( FILE *file )
{
  float var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
//******************************************************************** COMMENT
