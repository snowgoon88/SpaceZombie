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
 
  // Add a bool to switch between NoColor and DefaultColor in model.
  TwAddVarCB( meshBar, "DefColor", TW_TYPE_BOOLCPP, set_fg_color_cbk, get_fg_color_cbk, this /*clientData*/,
	      " label='(D)efColor' help='Switch between No or Default color' key=d"); 
}
//******************************************************************************

//******************************************************************************
void TW_CALL get_fg_color_cbk( void *value, void *clientData ) 
{
  //std::cout << "TWCALL get_fg_color_cbk" << "\n";

  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData
  *(bool *)value = mc->_viewer->_fg_color;
}
void TW_CALL set_fg_color_cbk( const void *value, void *clientData )
{
  std::cout << "MeshControl::set_fg_color_cbk = " << *(bool *)value << "\n";
  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData

  mc->_viewer->_fg_color = *(const bool *)value;
}
//******************************************************************************
