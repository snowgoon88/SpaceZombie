/* -*- coding: utf-8 -*- */

#ifndef __MESH_CONTROL_H__
#define __MESH_CONTROL_H__

#include "mesh_model.h"                 // MeshModel
#include "mesh_viewer_scigl.h"          // MeshControl
#include <string>                       // std::string
#include <AntTweakBar.h>                // TwBar

// Smart pointer
#ifdef HAVE_BOOST
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class MeshControl> MeshControlPtr;
#else
typedef class MeshControl * MeshControlPtr;
#endif

/**
 * Control MeshModel (and Viewer) using AntTweakBar.
 */
class MeshControl
{
public:
  /** Creation */
  MeshControl( MeshModelPtr model, MeshViewerPtr viewer);
  /** Destruction */
  virtual ~MeshControl();
  
  /** display string */
  std::string str_dump();

  /** Build the AntTweakBar */
  void build_bar();


  /** AntTweakBar to control MeshModel and MeshViewer */
  TwBar * meshBar;
  /** Model */
  MeshModelPtr _model;
  /** Viewer */
  MeshViewerPtr _viewer;

};

#endif // __MESH_CONTROL_H__