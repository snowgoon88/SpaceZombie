// -*- coding: utf-8 -*-

#ifndef __CELL_H__
#define __CELL_H__

#include "utils.h"
#include <string>

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class Cell> CellPtr;

/** 0=nord, 1=est, 2=sud, 3=ouest */
#define NB_DIR 4

/**
 *
 */
class Cell {
 public:
  //Cell(void);
  Cell( float x=0.0, float y=0.0, float z=0.0,
	      float ang_x=0.0, float ang_y=0.0 );
  Cell( Cell& other_c );
  virtual ~Cell(void);

  std::string repr_dump();

  float get_z_at( float x, float y );
  bool is_leaving_cell( float x, float y, unsigned int& dir );
  bool is_leaving_cell( TVec3 pos, unsigned int& dir );
  unsigned int get_dir_to( float x, float y );
  /** Compute point on the border when going from src to dest in dir */
  TVec3 clamp_to_cell( TVec3 src, TVec3 dest, unsigned int dir );
  //bool has_neigbour( CellPtr other_c );

  /** id */
  unsigned int _id;
  /** Position */
  float _x, _y, _z;
  /** Angles */
  float _ang_x, _ang_y;
  /** Neigbors */
  CellPtr _neighbors[NB_DIR];
  /** Separators */
  //SeparatorPtr _sep[NB_DIR];

  static unsigned int _nb_cells;
  static float size;
};

#endif // __CELL_H__
