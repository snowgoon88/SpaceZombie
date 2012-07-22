// -*- coding: utf-8 -*-

#ifndef __WORLD_H__
#define __WORLD_H__

#include <string>

// MVC
#include "model.h"
#include "ground.h"

// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class World> WorldPtr;


/**
 *
 */
class World : public Model
{
 public:
  World(void);
  World( World& other_w );
  virtual ~World(void);

  std::string repr_dump();

  void add_new_cell( float x, float y, float z );
  /**
   * Create a new room along Ox and Oy, origin of the room is x,y,z.
   */
  void add_new_room( float x, float y, float z,
		     unsigned int length_x, unsigned int length_y );
  /**
   * Create a corridor, between cells in src_cells and cells in des_cells.
   * src_cells must be a continuous strip of cells oriented at +PI/2 relative
   * to the direction of the corridor to built.
   */
  void connect_cells( std::vector< CellPtr > src_cells,
		      std::vector< CellPtr > des_cells );

  CellPtr get_cell_at( float x, float y, float z, bool verb=false );

  /** Where to set foot */
  GroundPtr _ground;
};

#endif // __WORLD_H__
