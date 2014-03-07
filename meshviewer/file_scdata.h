/* -*- coding: utf-8 -*- */

#ifndef __FILE_SCDATA_H__
#define __FILE_SCDATA_H__

#include <string>
#include <vector>
#include "utils.h"

/** 
 * Various function to read/write SCData files.
 */
class FileSCData
{
public:
  /** Creation */
  FileSCData(std::string filename);
  /** Destruction */
  virtual ~FileSCData();
  
  /** display string */
  std::string dump_string();

  /** size of a vertex */
  unsigned int _size_vertex;
  /** nb vertex */
  unsigned int _nb_vertex;
  /** data vertex xyz : 3*sizeof(float) */
  std::vector<TVec3> _v_xyz;
  /** data vertex rgba (default), certainly false */
  std::vector<TColorUC> _v_rgba;
  /** data indices : sizeof(unsigned short)*/
  std::vector<unsigned short> _v_indices;

  /** name of file */
  std::string _filename;
  /** raw data vertex : _size_vertex * sizeof(unsigned char)*/
  std::vector<unsigned char *> _raw_vertex;
  
  /** read file */
  void read( bool fg_verb = false );
};

#endif // __FILE_SCDATA_H__
