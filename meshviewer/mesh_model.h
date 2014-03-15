/* -*- coding: utf-8 -*- */

#ifndef __MESH_MODEL_H__
#define __MESH_MODEL_H__

#include <iostream>
#include <string>
#include "model.h"
#include "color.h"       // IColor abstract of various TColor<T>
#include "file_scdata.h"

#ifdef HAVE_BOOST
    #include <boost/shared_ptr.hpp>
    typedef boost::shared_ptr<class MeshModel> MeshModelPtr;
#else
    typedef class MeshModel * MeshModelPtr;
#endif

/**
 * A MeshModel is made of triangles of vertex:
 * + a vector of vertex (TVec3)
 * + [opt] a vector of indices : every set of 3 indices defines a triangle
 * + [opt] a vectof of color : one for every vertex
 */
class MeshModel : public Model
{
public:
  /** Creation */
  MeshModel();
  /** Destruction */
  virtual ~MeshModel();
  
  /** display string */
  std::string str_brief();
  void dump(std::ostream& out, unsigned int nb_shown=12 );

  /**
   * Read from FileSCData.
   * Copy vertex, indices and default color.
   */
  void read_from( FileSCData& fileobject );

  /** Vertex list */
  std::vector<TVec3> * _v_vertex;
  /** Triangle list : every 3 indices makes a Triangle */
  std::vector<unsigned short> * _v_indices;
  /** Vector of Abstract Color, can be NULL*/
  std::vector<IColor> * _v_color;
};

#endif // __MESH_MODEL_H__

