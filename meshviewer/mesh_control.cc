// -*- coding: utf-8 -*-

#include "mesh_control.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
MeshControl::MeshControl( MeshModelPtr model, MeshViewerPtr viewer )
{
  _model = model;
  _viewer = viewer;
}
/** Destruction */
MeshControl::~MeshControl()
{
}
//*********************************************************************** STRING
std::string MeshControl::str_dump()
{
  std::stringstream ss;
  
  ss << "MeshControl::dump_string()" << "\n";
  
  return ss.str();
}
//******************************************************************************
void MeshControl::build_bar()
{
  // Create a tweak bar
  meshBar = TwNewBar( "Mesh" );
  TwDefine(" Mesh label='Mesh TweakBar' position='10 60' help='Use this bar to alter the Mesh and its rendering' ");
  
  // Add a variable bool to control fg_wireframe in viewer.
  TwAddVarRW( meshBar, "WireFrame", TW_TYPE_BOOLCPP, &(_viewer->_fg_wireframe) ,
	      " label='(W)ire/Solid' help='Switch between WireFrame and Solid view' key=w");
  
}
