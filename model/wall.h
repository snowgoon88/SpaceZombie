// -*- coding: utf-8 -*-

#ifndef __WALL_H__
#define __WALL_H__

#include <string>

#include <boost/shared_ptr.hpp>
class Cell;
typedef boost::shared_ptr<class Cell> CellPtr;

#include "cell.h"

// Smart pointer
typedef boost::shared_ptr<class Wall> WallPtr;


/**
 *
 */
class Wall {
 public:
  //Wall(void);
  Wall( float x=0.0, float y=0.0, float z=0.0,
	      float ang_x=0.0, float ang_y=0.0 );
  Wall( Wall& other_c );
  virtual ~Wall(void);

  std::string repr_dump();

  /** id */
  unsigned int _id;
  /** Position */
  float _x, _y, _z;
  /** Angles */
  float _ang_x, _ang_y;
  /** Neigbors */
  WallPtr _neighbors[NB_DIR];
  /** Separators */
  //SeparatorPtr _sep[NB_DIR];

  static unsigned int _nb_cells;
};

#endif // __WALL_H__
