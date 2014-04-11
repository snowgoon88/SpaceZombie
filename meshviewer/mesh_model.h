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
  void dump(std::ostream& out, unsigned int nb_shown=12, unsigned int nb_start=0 );

  /** 
   * Attach to a FileSCData.
   * Copy vertex, indices and default color.
   */
  void attach( FileSCData *fileobject );
  /**
   * change custom_color using attached scdata */
  void custom_color_from_scdata( std::string type_name, unsigned int address );


  /** Type of Color used */
  enum EColor { NO_COLOR, DEFAULT_COLOR, CUSTOM_COLOR };
  EColor _e_color;

  /** Vertex list */
  std::vector<TVec3> * _v_vertex;
  /** Triangle list : every 3 indices makes a Triangle */
  std::vector<unsigned short> * _v_indices;  /**
   * Read from FileSCData.
   * Copy vertex, indices and default color.
   */
  void read_from( FileSCData& fileobject );

  /** Default color : grey for everyone */
  std::vector<IColorPtr> * _v_color_default;
  /** Vector of Abstract Color, can be NULL*/
  std::vector<IColorPtr> * _v_color_custom;

  /** Attached FileSCData */
  FileSCData * _scdata;
};

#endif // __MESH_MODEL_H__

