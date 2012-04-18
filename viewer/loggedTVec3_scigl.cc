/* -*- coding: utf-8 -*- */

// -*- coding: utf-8 -*-

#include "loggedTVec3_scigl.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
//LoggedTVec3Scigl::LoggedTVec3Scigl( LoggedTVec3Ptr model ) :
LoggedTVec3Scigl::LoggedTVec3Scigl( LoggedTPtr<TVec3>::Type model ) :
  Observer(), Object()
{
  _model = model;

  set_br_color( 0.0, 0.0, 0.0, 1.0 );
  
  std::ostringstream oss;
  oss << "LoggedTVec3Scigl_" << id_;
  set_name (oss.str());
}
/** Destruction */
LoggedTVec3Scigl::~LoggedTVec3Scigl()
{
}
//*********************************************************************** STRING
std::string LoggedTVec3Scigl::dump_string()
{
  std::stringstream ss;
  
  return ss.str();
}
//*********************************************************************** RENDER
void LoggedTVec3Scigl::render()
{
  compute_visibility();
  if (not get_visible()) return;

  // draw lines
  glColor4fv( get_br_color().data );
  glLineWidth( 1.0 );
  glBegin( GL_LINES ); {
    for( unsigned int i = 0; i < _model->_data.size(); ++i) {
      glVertex3f( _model->_data[i]._item(0), _model->_data[i]._item(1), _model->_data[i]._item(2) );      
    }
  }
  glEnd();
}
//*********************************************************************** UPDATE
void LoggedTVec3Scigl::update( int signal )
{
}
//******************************************************************************
