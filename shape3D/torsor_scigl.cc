// -*- coding: utf-8 -*-

#include "torsor_scigl.h"

// ******************************************************************** CREATION
TorsorScigl::TorsorScigl()
{
  set_visible (true);

  std::ostringstream oss;
  oss << "TorsorScigl_" << id_;
  set_name (oss.str());

  _arr_res.set_position( TVec3(0, 0, 0) );
  _arr_mom.set_position( TVec3(0, 0, 0) );
}
TorsorScigl::TorsorScigl( Torsor& t)
{
  set_visible (true);

  std::ostringstream oss;
  oss << "TorsorScigl_" << id_;
  set_name (oss.str());

  _arr_res.set_position( TVec3(0, 0, 0) );
  _arr_res.compute_from_vec( t._r );
  _arr_mom.set_position( TVec3(0, 0, 0) );
  _arr_mom.compute_from_vec( t._m );
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

   glPopMatrix();
}
// *****************************************************************************
