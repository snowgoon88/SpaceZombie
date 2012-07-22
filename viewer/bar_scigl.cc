// -*- coding: utf-8 -*-

#include "bar_scigl.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
BarScigl::BarScigl() : Observer(), Object()
{
  // SCIGL
  set_fg_color( 0.0f, 0.0f, 0.0f, 1.0f );
  set_bg_color( 0.0f, 0.0f, 0.0f, 1.0f );
  set_br_color( 0.0f, 0.0f, 0.0f, 1.0f );
  set_visible( true );

  std::ostringstream oss;
  oss << "Bar_" << id_;
  set_name (oss.str());
}
BarScigl::BarScigl(BarPtr model) : Observer(), Object()
{
  _model = model;
  // TODO : don't know how to do that with smart pointer !!
  // BarSciglPtr this_ptr = BarSciglPtr( this );
  //_model->attach_observer( this_ptr );
  
  // SCIGL
  set_fg_color( 0.0f, 0.0f, 0.0f, 1.0f );
  set_bg_color( 0.0f, 0.0f, 0.0f, 1.0f );
  set_br_color( 0.0f, 0.0f, 0.0f, 1.0f );
  set_visible( true );

  std::ostringstream oss;
  oss << "Bar_" << id_;
  set_name (oss.str());
}
/** Destruction */
BarScigl::~BarScigl()
{
}
//*********************************************************************** STRING
std::string BarScigl::dump_string()
{
  std::stringstream ss;
  
  return ss.str();
}
//*********************************************************************** RENDER
void BarScigl::render( void ) 
{
  compute_visibility();
  if (not get_visible()) return;

  //std::cout << "BarScigl start=" << line_repr(_model->_pt_start) << " end=" << _model->_pt_end << "\n";

  // draw line
  glColor4fv( get_fg_color().data );
  glLineWidth( 1.0 );
  glBegin( GL_LINES ); {
    glVertex3f( _model->_pt_start(0), _model->_pt_start(1), _model->_pt_start(2) );
    glVertex3f( _model->_pt_end(0), _model->_pt_end(1), _model->_pt_end(2) );   
  }
  glEnd();
}
//*********************************************************************** UPDATE
void BarScigl::update( int signal ) 
{
}
//******************************************************************************
