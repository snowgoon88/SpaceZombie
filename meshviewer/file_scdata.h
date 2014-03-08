/* -*- coding: utf-8 -*- */

#ifndef __FILE_SCDATA_H__
#define __FILE_SCDATA_H__

#include <string>
#include <vector>
#include "utils.h"

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

  /** size of a vertex */
  unsigned int _size_vertex;
  /** nb vertex */
  unsigned int _nb_vertex;
  /** data vertex xyz : 3*sizeof(float) */
  std::vector<TVec3> _v_xyz;
  /** data vertex rgba (default), certainly false */
  std::vector<TColorUC> _v_rgba_uc;
  /** data vertex rgba in "normal" char */
  std::vector<TColorC> _v_rgba_c;
  /** data indices : sizeof(unsigned short)*/
  std::vector<unsigned short> _v_indices;

  /** name of file */
  std::string _filename;
  /** raw data vertex : _size_vertex * sizeof(unsigned char)*/
  std::vector<unsigned char *> _raw_vertex;
  
  /** read file */
  void read( bool fg_verb = false );
  
  /** read vertex starting at byte 'idx_start' as a TColorUC object */
  void get_TColorUC( std::vector<TColorUC> *v_col,
		     unsigned int idx_start = 0x0C);

  // ****** PROTECTED *****
  // @todo template ??
  unsigned char read_uchar( FILE *file );
  unsigned int read_ushort( FILE *file );
  unsigned int read_uint( FILE *file );
  float read_float( FILE *file );
};

#endif // __FILE_SCDATA_H__
