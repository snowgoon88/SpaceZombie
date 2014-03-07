/* -*- coding: utf-8 -*- */

#ifndef __MESH_MODEL_H__
#define __MESH_MODEL_H__

/**
 * A MeshModel is made of triangles of vertex:
 * + a vector of vertex (TVec3)
 * + [opt] a vector of indices : every set of 3 indices defines a triangle
 * + [opt] a vectof of color : one for every vertex
 */
class MeshModel
{
public:
  /** Creation */
  MeshModel(std::string name);
  /** Destruction */
  virtual ~MeshModel();
  
  /** display string */
  std::string dump_string();


  /** Vertex list */
  std::vector<TVec3> _v_vertex;
  /** Triangle list : every 3 indices makes a Triangle */
  std::vector<unsigned int> _v_indices;
  /** @test : Vector of TColorUC colors */
  std::vector<TColorUC> _v_color_uc;
  /** @todo : Vector of Color */
};

#endif // __MESH_MODEL_H__

