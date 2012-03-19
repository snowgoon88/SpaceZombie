// -*- coding: utf-8 -*-

#ifndef __GROUND_H__
#define __GROUND_H__

#include <string>
#include <vector>

#include "cell.h"

// Smart pointer
#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class Ground> GroundPtr;
#else
    typedef class Ground * GroundPtr;
#endif

/**
 *
 */
class Ground {
 public:
  Ground(void);
  Ground( Ground& other_g );
  virtual ~Ground(void);

  std::string repr_dump();

  /** Cells */
  std::vector<CellPtr> _cells;
};

#endif // __GROUND_H__
