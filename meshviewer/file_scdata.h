/* -*- coding: utf-8 -*- */

#ifndef __FILE_SCDATA_H__
#define __FILE_SCDATA_H__

#include <string>
#include <vector>
#include "utils.h"
#include "color.h"     // IColorPtr, TColor<T>

/** 
 * Various function to read/write SCData files.
 *
 * @todo Struct of a SCData file :
 * 
 *
 */
class FileSCData
{
public:
  /** Creation */
  FileSCData(std::string filename);
  /** Destruction */
  virtual ~FileSCData();
  
  /** display brief string */
  std::string str_brief();
  /** display triangle (vertex, color) at index */
  std::string str_triangle(unsigned int index);
  /** dump on a stream */
  void dump( std::ostream& out );
  /** display raw memory at index */
  std::string str_mem(unsigned int index);

  /** size of a vertex */
  unsigned int _size_vertex;
  /** nb vertex */
  unsigned int _nb_vertex;
  /** data vertex xyz : 3*sizeof(float) */
  std::vector<TVec3> _v_xyz;
  /** data vertex uv : 2*sizeof(float) */
  std::vector<TVec2> _v_uv;
  /** data vertex rgba (default), certainly false */
  std::vector<TColorUC> _v_rgba_uc;
  /** data vertex rgba in "normal" char */
  std::vector<TColorC> _v_rgba_c;
  /** data indices : sizeof(unsigned short)*/
  std::vector<unsigned short> _v_indices;
  /** vertex color */
  std::vector<IColorPtr> _v_color;

  /** name of file */
  std::string _filename;
  /** raw data vertex : _size_vertex * sizeof(char)*/
  std::vector<char *> _raw_vertex;
  
  /** read file */
  void read( bool fg_verb = false );
  
  /** read vertex starting at byte 'idx_start' as a TColorUC object */
  void get_TColorUC( std::vector<TColorUC> *v_col,
		     unsigned int idx_start = 0x0C);
 template<typename T>
   void read_v_color( unsigned int idx_start )
   {
     _v_color.clear();
     for (unsigned int i=0; i < _raw_vertex.size(); ++i) {
       char * vertex = _raw_vertex[i];
       IColorPtr colptr = IColorPtr( new TColor<T>( &(vertex[idx_start]) ));
       _v_color.push_back( colptr );
     }
   }
  // ****** PROTECTED *****
  // @todo template ??
  unsigned char read_uchar( FILE *file );
  unsigned int read_ushort( FILE *file );
  unsigned int read_uint( FILE *file );
  float read_float( FILE *file );
};

#endif // __FILE_SCDATA_H__
