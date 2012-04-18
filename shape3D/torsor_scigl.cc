// -*- coding: utf-8 -*-

#include "torsor_scigl.h"

// ******************************************************************** CREATION
TorsorScigl::TorsorScigl()
{
  set_visible (true);
  set_color( 0, 0, 0, 1);

  std::ostringstream oss;
  oss << "TorsorScigl_" << id_;
  set_name (oss.str());

  _arr_res.set_position( TVec3(0, 0, 0) );
  _arr_mom.set_position( TVec3(0, 0, 0) );
  _arr_mom._fg_moment = true;

  _fg_axis = false;
}
TorsorScigl::TorsorScigl( Torsor& t)
{
  set_visible (true);
  set_color( 0, 0, 0, 1);

  std::ostringstream oss;
  oss << "TorsorScigl_" << id_;
  set_name (oss.str());

  _arr_res.set_position( t._p );
  _arr_res.compute_from_vec( t._r );
  _arr_mom.set_position( t._p );
  _arr_mom._fg_moment = true;
  _arr_mom.compute_from_vec( t._m );

  _fg_axis = false;
  _pt_axis = t._p - t.get_Ip();
  _dir_axis = t._r;
}
TorsorScigl::TorsorScigl( TorsorPtr model )
{
  _model = model;

  set_visible (true);
  set_color( 0, 0, 0, 1);

  std::ostringstream oss;
  oss << "TorsorScigl_" << id_;
  set_name (oss.str());

  _fg_axis = false;

  update();
}
TorsorScigl::~TorsorScigl()
{
}
// ********************************************************************** RENDER
void TorsorScigl::render (void)
{
  compute_visibility();
  if (not get_visible()) return;

  glPushMatrix();
  glTranslatef (get_position().x, get_position().y, get_position().z);
  
  _arr_res.render();
  _arr_mom.render();

  // draw axis ? (color given by arrows)
  if( _fg_axis ) {
    glPushAttrib( GL_ENABLE_BIT );
    
    glEnable( GL_LINE_STIPPLE );
    glLineStipple(1, 0x00FF );  /*  dashed  */
    glBegin(GL_LINES); {
      glVertex3f( (_pt_axis-5.0*_dir_axis)(0), (_pt_axis-5.0*_dir_axis)(1), (_pt_axis-5.0*_dir_axis)(2) );
      glVertex3f( (_pt_axis+5.0*_dir_axis)(0), (_pt_axis+5.0*_dir_axis)(1), (_pt_axis+5.0*_dir_axis)(2) );
    }
    glEnd();
    glPopAttrib();
  }
  
  glPopMatrix();
}
//******************************************************************************
void TorsorScigl::update( int signal ) 
{
  _arr_res.set_position( _model->_p );
  _arr_res.compute_from_vec( _model->_r );
  _arr_mom.set_position( _model->_p );
  _arr_mom.compute_from_vec( _model->_m );

  _pt_axis = _model->_p - _model->get_Ip();
  _dir_axis = _model->_r;
}
// *********************************************************************** COLOR
void TorsorScigl::set_color( float r, float g, float b, float a ) 
{
  set_color( Color( r,g,b,a ));
}
void TorsorScigl::set_color( Color color )
{
  
  _arr_res.set_fg_color( color );
  _arr_res.set_br_color( color );
  _arr_mom.set_fg_color( color );
  _arr_mom.set_br_color( color );
}
//******************************************************************************
