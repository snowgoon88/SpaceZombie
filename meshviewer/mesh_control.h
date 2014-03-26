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

  /** string for setting where custom color is read */
  std::string _color_custom_str;
};
//@{
/** CBK function to alter viewer->_fg_color */
void TW_CALL get_fg_color_cbk( void *value, void *clientData );
void TW_CALL set_fg_color_cbk( const void *value, void *clientData ); 
//@}
//@{
/** CBK function to alter control->_color_custom_str */
void TW_CALL set_custom_color_str_cbk(const void *value, void * clientData );
void TW_CALL get_custom_color_str_cbk(void *value, void *clientData);
//@}
#endif // __MESH_CONTROL_H__
